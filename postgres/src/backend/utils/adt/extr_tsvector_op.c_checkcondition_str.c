#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WordEntryPos ;
struct TYPE_11__ {int /*<<< orphan*/  len; scalar_t__ pos; } ;
typedef  TYPE_1__ WordEntry ;
struct TYPE_14__ {scalar_t__ values; scalar_t__ operand; TYPE_1__* arre; TYPE_1__* arrb; } ;
struct TYPE_13__ {int npos; int allocated; int /*<<< orphan*/ * pos; } ;
struct TYPE_12__ {int /*<<< orphan*/  length; scalar_t__ distance; scalar_t__ prefix; } ;
typedef  TYPE_2__ QueryOperand ;
typedef  TYPE_3__ ExecPhraseData ;
typedef  TYPE_4__ CHKVAL ;

/* Variables and functions */
 int checkclass_str (TYPE_4__*,TYPE_1__*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  compareWordEntryPos ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int qunique (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * repalloc (int /*<<< orphan*/ *,int) ; 
 int tsCompareString (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
checkcondition_str(void *checkval, QueryOperand *val, ExecPhraseData *data)
{
	CHKVAL	   *chkval = (CHKVAL *) checkval;
	WordEntry  *StopLow = chkval->arrb;
	WordEntry  *StopHigh = chkval->arre;
	WordEntry  *StopMiddle = StopHigh;
	int			difference = -1;
	bool		res = false;

	/* Loop invariant: StopLow <= val < StopHigh */
	while (StopLow < StopHigh)
	{
		StopMiddle = StopLow + (StopHigh - StopLow) / 2;
		difference = tsCompareString(chkval->operand + val->distance,
									 val->length,
									 chkval->values + StopMiddle->pos,
									 StopMiddle->len,
									 false);

		if (difference == 0)
		{
			/* Check weight info & fill 'data' with positions */
			res = checkclass_str(chkval, StopMiddle, val, data);
			break;
		}
		else if (difference > 0)
			StopLow = StopMiddle + 1;
		else
			StopHigh = StopMiddle;
	}

	if ((!res || data) && val->prefix)
	{
		WordEntryPos *allpos = NULL;
		int			npos = 0,
					totalpos = 0;

		/*
		 * there was a failed exact search, so we should scan further to find
		 * a prefix match. We also need to do so if caller needs position info
		 */
		if (StopLow >= StopHigh)
			StopMiddle = StopHigh;

		while ((!res || data) && StopMiddle < chkval->arre &&
			   tsCompareString(chkval->operand + val->distance,
							   val->length,
							   chkval->values + StopMiddle->pos,
							   StopMiddle->len,
							   true) == 0)
		{
			if (data)
			{
				/*
				 * We need to join position information
				 */
				res = checkclass_str(chkval, StopMiddle, val, data);

				if (res)
				{
					while (npos + data->npos >= totalpos)
					{
						if (totalpos == 0)
						{
							totalpos = 256;
							allpos = palloc(sizeof(WordEntryPos) * totalpos);
						}
						else
						{
							totalpos *= 2;
							allpos = repalloc(allpos, sizeof(WordEntryPos) * totalpos);
						}
					}

					memcpy(allpos + npos, data->pos, sizeof(WordEntryPos) * data->npos);
					npos += data->npos;
				}
			}
			else
			{
				res = checkclass_str(chkval, StopMiddle, val, NULL);
			}

			StopMiddle++;
		}

		if (res && data)
		{
			/* Sort and make unique array of found positions */
			data->pos = allpos;
			qsort(data->pos, npos, sizeof(WordEntryPos), compareWordEntryPos);
			data->npos = qunique(data->pos, npos, sizeof(WordEntryPos),
								 compareWordEntryPos);
			data->allocated = true;
		}
	}

	return res;
}