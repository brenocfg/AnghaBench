#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_14__ {int startpos; int endpos; int curlen; int poslen; int in; int excluded; } ;
struct TYPE_13__ {int curwords; TYPE_1__* words; } ;
struct TYPE_12__ {int len; int /*<<< orphan*/  type; int /*<<< orphan*/  in; } ;
typedef  int /*<<< orphan*/  TSQuery ;
typedef  TYPE_2__ HeadlineParsedText ;
typedef  TYPE_3__ CoverPos ;

/* Variables and functions */
 scalar_t__ NOENDTOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONWORDTOKEN (int /*<<< orphan*/ ) ; 
 int PG_INT32_MAX ; 
 int /*<<< orphan*/  get_next_fragment (TYPE_2__*,int*,int*,int*,int*,int) ; 
 scalar_t__ hlCover (TYPE_2__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  mark_fragment (TYPE_2__*,int,int,int) ; 
 TYPE_3__* palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 TYPE_3__* repalloc (TYPE_3__*,int) ; 

__attribute__((used)) static void
mark_hl_fragments(HeadlineParsedText *prs, TSQuery query, int highlight,
				  int shortword, int min_words,
				  int max_words, int max_fragments)
{
	int32		poslen,
				curlen,
				i,
				f,
				num_f = 0;
	int32		stretch,
				maxstretch,
				posmarker;

	int32		startpos = 0,
				endpos = 0,
				p = 0,
				q = 0;

	int32		numcovers = 0,
				maxcovers = 32;

	int32		minI,
				minwords,
				maxitems;
	CoverPos   *covers;

	covers = palloc(maxcovers * sizeof(CoverPos));

	/* get all covers */
	while (hlCover(prs, query, &p, &q))
	{
		startpos = p;
		endpos = q;

		/*
		 * Break the cover into smaller fragments such that each fragment has
		 * at most max_words. Also ensure that each end of the fragment is a
		 * query word. This will allow us to stretch the fragment in either
		 * direction
		 */

		while (startpos <= endpos)
		{
			get_next_fragment(prs, &startpos, &endpos, &curlen, &poslen, max_words);
			if (numcovers >= maxcovers)
			{
				maxcovers *= 2;
				covers = repalloc(covers, sizeof(CoverPos) * maxcovers);
			}
			covers[numcovers].startpos = startpos;
			covers[numcovers].endpos = endpos;
			covers[numcovers].curlen = curlen;
			covers[numcovers].poslen = poslen;
			covers[numcovers].in = 0;
			covers[numcovers].excluded = 0;
			numcovers++;
			startpos = endpos + 1;
			endpos = q;
		}
		/* move p to generate the next cover */
		p++;
	}

	/* choose best covers */
	for (f = 0; f < max_fragments; f++)
	{
		maxitems = 0;
		minwords = PG_INT32_MAX;
		minI = -1;

		/*
		 * Choose the cover that contains max items. In case of tie choose the
		 * one with smaller number of words.
		 */
		for (i = 0; i < numcovers; i++)
		{
			if (!covers[i].in && !covers[i].excluded &&
				(maxitems < covers[i].poslen || (maxitems == covers[i].poslen
												 && minwords > covers[i].curlen)))
			{
				maxitems = covers[i].poslen;
				minwords = covers[i].curlen;
				minI = i;
			}
		}
		/* if a cover was found mark it */
		if (minI >= 0)
		{
			covers[minI].in = 1;
			/* adjust the size of cover */
			startpos = covers[minI].startpos;
			endpos = covers[minI].endpos;
			curlen = covers[minI].curlen;
			/* stretch the cover if cover size is lower than max_words */
			if (curlen < max_words)
			{
				/* divide the stretch on both sides of cover */
				maxstretch = (max_words - curlen) / 2;

				/*
				 * first stretch the startpos stop stretching if 1. we hit the
				 * beginning of document 2. exceed maxstretch 3. we hit an
				 * already marked fragment
				 */
				stretch = 0;
				posmarker = startpos;
				for (i = startpos - 1; i >= 0 && stretch < maxstretch && !prs->words[i].in; i--)
				{
					if (!NONWORDTOKEN(prs->words[i].type))
					{
						curlen++;
						stretch++;
					}
					posmarker = i;
				}
				/* cut back startpos till we find a non short token */
				for (i = posmarker; i < startpos && (NOENDTOKEN(prs->words[i].type) || prs->words[i].len <= shortword); i++)
				{
					if (!NONWORDTOKEN(prs->words[i].type))
						curlen--;
				}
				startpos = i;
				/* now stretch the endpos as much as possible */
				posmarker = endpos;
				for (i = endpos + 1; i < prs->curwords && curlen < max_words && !prs->words[i].in; i++)
				{
					if (!NONWORDTOKEN(prs->words[i].type))
						curlen++;
					posmarker = i;
				}
				/* cut back endpos till we find a non-short token */
				for (i = posmarker; i > endpos && (NOENDTOKEN(prs->words[i].type) || prs->words[i].len <= shortword); i--)
				{
					if (!NONWORDTOKEN(prs->words[i].type))
						curlen--;
				}
				endpos = i;
			}
			covers[minI].startpos = startpos;
			covers[minI].endpos = endpos;
			covers[minI].curlen = curlen;
			/* Mark the chosen fragments (covers) */
			mark_fragment(prs, highlight, startpos, endpos);
			num_f++;
			/* exclude overlapping covers */
			for (i = 0; i < numcovers; i++)
			{
				if (i != minI && ((covers[i].startpos >= covers[minI].startpos && covers[i].startpos <= covers[minI].endpos) || (covers[i].endpos >= covers[minI].startpos && covers[i].endpos <= covers[minI].endpos)))
					covers[i].excluded = 1;
			}
		}
		else
			break;
	}

	/* show at least min_words we have not marked anything */
	if (num_f <= 0)
	{
		startpos = endpos = curlen = 0;
		for (i = 0; i < prs->curwords && curlen < min_words; i++)
		{
			if (!NONWORDTOKEN(prs->words[i].type))
				curlen++;
			endpos = i;
		}
		mark_fragment(prs, highlight, startpos, endpos);
	}
	pfree(covers);
}