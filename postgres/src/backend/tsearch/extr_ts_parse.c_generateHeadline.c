#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int int16 ;
struct TYPE_5__ {int curwords; int stopsellen; int startsellen; int fragdelimlen; int /*<<< orphan*/  stopsel; int /*<<< orphan*/  startsel; int /*<<< orphan*/  fragdelim; TYPE_1__* words; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  word; int /*<<< orphan*/  repeated; scalar_t__ selected; int /*<<< orphan*/  skip; scalar_t__ replace; scalar_t__ in; } ;
typedef  TYPE_1__ HeadlineWordEntry ;
typedef  TYPE_2__ HeadlineParsedText ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 int VARHDRSZ ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 

text *
generateHeadline(HeadlineParsedText *prs)
{
	text	   *out;
	char	   *ptr;
	int			len = 128;
	int			numfragments = 0;
	int16		infrag = 0;

	HeadlineWordEntry *wrd = prs->words;

	out = (text *) palloc(len);
	ptr = ((char *) out) + VARHDRSZ;

	while (wrd - prs->words < prs->curwords)
	{
		while (wrd->len + prs->stopsellen + prs->startsellen + prs->fragdelimlen + (ptr - ((char *) out)) >= len)
		{
			int			dist = ptr - ((char *) out);

			len *= 2;
			out = (text *) repalloc(out, len);
			ptr = ((char *) out) + dist;
		}

		if (wrd->in && !wrd->repeated)
		{
			if (!infrag)
			{

				/* start of a new fragment */
				infrag = 1;
				numfragments++;
				/* add a fragment delimiter if this is after the first one */
				if (numfragments > 1)
				{
					memcpy(ptr, prs->fragdelim, prs->fragdelimlen);
					ptr += prs->fragdelimlen;
				}

			}
			if (wrd->replace)
			{
				*ptr = ' ';
				ptr++;
			}
			else if (!wrd->skip)
			{
				if (wrd->selected)
				{
					memcpy(ptr, prs->startsel, prs->startsellen);
					ptr += prs->startsellen;
				}
				memcpy(ptr, wrd->word, wrd->len);
				ptr += wrd->len;
				if (wrd->selected)
				{
					memcpy(ptr, prs->stopsel, prs->stopsellen);
					ptr += prs->stopsellen;
				}
			}
		}
		else if (!wrd->repeated)
		{
			if (infrag)
				infrag = 0;
			pfree(wrd->word);
		}

		wrd++;
	}

	SET_VARSIZE(out, ptr - ((char *) out));
	return out;
}