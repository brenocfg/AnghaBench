#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  size_t int32 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_11__ {int /*<<< orphan*/  qoperator; int /*<<< orphan*/  cfg_id; } ;
struct TYPE_10__ {int lenwords; size_t curwords; TYPE_2__* words; scalar_t__ pos; } ;
struct TYPE_8__ {scalar_t__ pos; } ;
struct TYPE_9__ {scalar_t__ nvariant; int flags; struct TYPE_9__* word; int /*<<< orphan*/  len; TYPE_1__ pos; } ;
typedef  int /*<<< orphan*/  TSQueryParserState ;
typedef  TYPE_2__ ParsedWord ;
typedef  TYPE_3__ ParsedText ;
typedef  TYPE_4__ MorphOpaque ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_AND ; 
 int /*<<< orphan*/  OP_OR ; 
 int TSL_PREFIX ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  parsetext (int /*<<< orphan*/ ,TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 int /*<<< orphan*/  pushOperator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pushStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushValue (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pushval_morph(Datum opaque, TSQueryParserState state, char *strval, int lenval, int16 weight, bool prefix)
{
	int32		count = 0;
	ParsedText	prs;
	uint32		variant,
				pos = 0,
				cntvar = 0,
				cntpos = 0,
				cnt = 0;
	MorphOpaque *data = (MorphOpaque *) DatumGetPointer(opaque);

	prs.lenwords = 4;
	prs.curwords = 0;
	prs.pos = 0;
	prs.words = (ParsedWord *) palloc(sizeof(ParsedWord) * prs.lenwords);

	parsetext(data->cfg_id, &prs, strval, lenval);

	if (prs.curwords > 0)
	{
		while (count < prs.curwords)
		{
			/*
			 * Were any stop words removed? If so, fill empty positions with
			 * placeholders linked by an appropriate operator.
			 */
			if (pos > 0 && pos + 1 < prs.words[count].pos.pos)
			{
				while (pos + 1 < prs.words[count].pos.pos)
				{
					/* put placeholders for each missing stop word */
					pushStop(state);
					if (cntpos)
						pushOperator(state, data->qoperator, 1);
					cntpos++;
					pos++;
				}
			}

			/* save current word's position */
			pos = prs.words[count].pos.pos;

			/* Go through all variants obtained from this token */
			cntvar = 0;
			while (count < prs.curwords && pos == prs.words[count].pos.pos)
			{
				variant = prs.words[count].nvariant;

				/* Push all words belonging to the same variant */
				cnt = 0;
				while (count < prs.curwords &&
					   pos == prs.words[count].pos.pos &&
					   variant == prs.words[count].nvariant)
				{
					pushValue(state,
							  prs.words[count].word,
							  prs.words[count].len,
							  weight,
							  ((prs.words[count].flags & TSL_PREFIX) || prefix));
					pfree(prs.words[count].word);
					if (cnt)
						pushOperator(state, OP_AND, 0);
					cnt++;
					count++;
				}

				if (cntvar)
					pushOperator(state, OP_OR, 0);
				cntvar++;
			}

			if (cntpos)
			{
				/* distance may be useful */
				pushOperator(state, data->qoperator, 1);
			}

			cntpos++;
		}

		pfree(prs.words);

	}
	else
		pushStop(state);
}