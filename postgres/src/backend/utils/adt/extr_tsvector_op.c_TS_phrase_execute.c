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
typedef  int uint32 ;
struct TYPE_12__ {int oper; int distance; int /*<<< orphan*/  left; } ;
struct TYPE_14__ {scalar_t__ type; TYPE_1__ qoperator; } ;
struct TYPE_13__ {int negate; int width; scalar_t__ npos; } ;
typedef  int (* TSExecuteCallback ) (void*,int /*<<< orphan*/ *,TYPE_2__*) ;
typedef  int /*<<< orphan*/  Rdata ;
typedef  int /*<<< orphan*/  QueryOperand ;
typedef  TYPE_3__ QueryItem ;
typedef  int /*<<< orphan*/  Ldata ;
typedef  TYPE_2__ ExecPhraseData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int Max (int,int) ; 
 scalar_t__ Min (scalar_t__,scalar_t__) ; 
#define  OP_AND 131 
#define  OP_NOT 130 
#define  OP_OR 129 
#define  OP_PHRASE 128 
 scalar_t__ QI_VAL ; 
 int TSPO_BOTH ; 
 int TSPO_L_ONLY ; 
 int TSPO_R_ONLY ; 
 int TS_EXEC_PHRASE_NO_POS ; 
 int TS_phrase_output (TYPE_2__*,TYPE_2__*,TYPE_2__*,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
TS_phrase_execute(QueryItem *curitem, void *arg, uint32 flags,
				  TSExecuteCallback chkcond,
				  ExecPhraseData *data)
{
	ExecPhraseData Ldata,
				Rdata;
	bool		lmatch,
				rmatch;
	int			Loffset,
				Roffset,
				maxwidth;

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	if (curitem->type == QI_VAL)
		return chkcond(arg, (QueryOperand *) curitem, data);

	switch (curitem->qoperator.oper)
	{
		case OP_NOT:

			/*
			 * Because a "true" result with no specific positions is taken as
			 * uncertain, we need no special care here for !TS_EXEC_CALC_NOT.
			 * If it's a false positive, the right things happen anyway.
			 *
			 * Also, we need not touch data->width, since a NOT operation does
			 * not change the match width.
			 */
			if (TS_phrase_execute(curitem + 1, arg, flags, chkcond, data))
			{
				if (data->npos > 0)
				{
					/* we have some positions, invert negate flag */
					data->negate = !data->negate;
					return true;
				}
				else if (data->negate)
				{
					/* change "match everywhere" to "match nowhere" */
					data->negate = false;
					return false;
				}
				/* match positions are, and remain, uncertain */
				return true;
			}
			else
			{
				/* change "match nowhere" to "match everywhere" */
				Assert(data->npos == 0 && !data->negate);
				data->negate = true;
				return true;
			}

		case OP_PHRASE:
		case OP_AND:
			memset(&Ldata, 0, sizeof(Ldata));
			memset(&Rdata, 0, sizeof(Rdata));

			if (!TS_phrase_execute(curitem + curitem->qoperator.left,
								   arg, flags, chkcond, &Ldata))
				return false;

			if (!TS_phrase_execute(curitem + 1,
								   arg, flags, chkcond, &Rdata))
				return false;

			/*
			 * If either operand has no position information, then we can't
			 * return position data, only a "possible match" result. "Possible
			 * match" answers are only wanted when TS_EXEC_PHRASE_NO_POS flag
			 * is set, otherwise return false.
			 */
			if ((Ldata.npos == 0 && !Ldata.negate) ||
				(Rdata.npos == 0 && !Rdata.negate))
				return (flags & TS_EXEC_PHRASE_NO_POS) ? true : false;

			if (curitem->qoperator.oper == OP_PHRASE)
			{
				/*
				 * Compute Loffset and Roffset suitable for phrase match, and
				 * compute overall width of whole phrase match.
				 */
				Loffset = curitem->qoperator.distance + Rdata.width;
				Roffset = 0;
				if (data)
					data->width = curitem->qoperator.distance +
						Ldata.width + Rdata.width;
			}
			else
			{
				/*
				 * For OP_AND, set output width and alignment like OP_OR (see
				 * comment below)
				 */
				maxwidth = Max(Ldata.width, Rdata.width);
				Loffset = maxwidth - Ldata.width;
				Roffset = maxwidth - Rdata.width;
				if (data)
					data->width = maxwidth;
			}

			if (Ldata.negate && Rdata.negate)
			{
				/* !L & !R: treat as !(L | R) */
				(void) TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_BOTH | TSPO_L_ONLY | TSPO_R_ONLY,
										Loffset, Roffset,
										Ldata.npos + Rdata.npos);
				if (data)
					data->negate = true;
				return true;
			}
			else if (Ldata.negate)
			{
				/* !L & R */
				return TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_R_ONLY,
										Loffset, Roffset,
										Rdata.npos);
			}
			else if (Rdata.negate)
			{
				/* L & !R */
				return TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_L_ONLY,
										Loffset, Roffset,
										Ldata.npos);
			}
			else
			{
				/* straight AND */
				return TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_BOTH,
										Loffset, Roffset,
										Min(Ldata.npos, Rdata.npos));
			}

		case OP_OR:
			memset(&Ldata, 0, sizeof(Ldata));
			memset(&Rdata, 0, sizeof(Rdata));

			lmatch = TS_phrase_execute(curitem + curitem->qoperator.left,
									   arg, flags, chkcond, &Ldata);
			rmatch = TS_phrase_execute(curitem + 1,
									   arg, flags, chkcond, &Rdata);

			if (!lmatch && !rmatch)
				return false;

			/*
			 * If a valid operand has no position information, then we can't
			 * return position data, only a "possible match" result. "Possible
			 * match" answers are only wanted when TS_EXEC_PHRASE_NO_POS flag
			 * is set, otherwise return false.
			 */
			if ((lmatch && Ldata.npos == 0 && !Ldata.negate) ||
				(rmatch && Rdata.npos == 0 && !Rdata.negate))
				return (flags & TS_EXEC_PHRASE_NO_POS) ? true : false;

			/*
			 * Cope with undefined output width from failed submatch.  (This
			 * takes less code than trying to ensure that all failure returns
			 * set data->width to zero.)
			 */
			if (!lmatch)
				Ldata.width = 0;
			if (!rmatch)
				Rdata.width = 0;

			/*
			 * For OP_AND and OP_OR, report the width of the wider of the two
			 * inputs, and align the narrower input's positions to the right
			 * end of that width.  This rule deals at least somewhat
			 * reasonably with cases like "x <-> (y | z <-> q)".
			 */
			maxwidth = Max(Ldata.width, Rdata.width);
			Loffset = maxwidth - Ldata.width;
			Roffset = maxwidth - Rdata.width;
			data->width = maxwidth;

			if (Ldata.negate && Rdata.negate)
			{
				/* !L | !R: treat as !(L & R) */
				(void) TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_BOTH,
										Loffset, Roffset,
										Min(Ldata.npos, Rdata.npos));
				data->negate = true;
				return true;
			}
			else if (Ldata.negate)
			{
				/* !L | R: treat as !(L & !R) */
				(void) TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_L_ONLY,
										Loffset, Roffset,
										Ldata.npos);
				data->negate = true;
				return true;
			}
			else if (Rdata.negate)
			{
				/* L | !R: treat as !(!L & R) */
				(void) TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_R_ONLY,
										Loffset, Roffset,
										Rdata.npos);
				data->negate = true;
				return true;
			}
			else
			{
				/* straight OR */
				return TS_phrase_output(data, &Ldata, &Rdata,
										TSPO_BOTH | TSPO_L_ONLY | TSPO_R_ONLY,
										Loffset, Roffset,
										Ldata.npos + Rdata.npos);
			}

		default:
			elog(ERROR, "unrecognized operator: %d", curitem->qoperator.oper);
	}

	/* not reachable, but keep compiler quiet */
	return false;
}