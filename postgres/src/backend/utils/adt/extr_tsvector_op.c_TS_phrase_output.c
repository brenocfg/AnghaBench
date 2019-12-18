#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WordEntryPos ;
struct TYPE_5__ {int npos; int* pos; int allocated; } ;
typedef  TYPE_1__ ExecPhraseData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int INT_MAX ; 
 int TSPO_BOTH ; 
 int TSPO_L_ONLY ; 
 int TSPO_R_ONLY ; 
 int WEP_GETPOS (int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static bool
TS_phrase_output(ExecPhraseData *data,
				 ExecPhraseData *Ldata,
				 ExecPhraseData *Rdata,
				 int emit,
				 int Loffset,
				 int Roffset,
				 int max_npos)
{
	int			Lindex,
				Rindex;

	/* Loop until both inputs are exhausted */
	Lindex = Rindex = 0;
	while (Lindex < Ldata->npos || Rindex < Rdata->npos)
	{
		int			Lpos,
					Rpos;
		int			output_pos = 0;

		/*
		 * Fetch current values to compare.  WEP_GETPOS() is needed because
		 * ExecPhraseData->data can point to a tsvector's WordEntryPosVector.
		 */
		if (Lindex < Ldata->npos)
			Lpos = WEP_GETPOS(Ldata->pos[Lindex]) + Loffset;
		else
		{
			/* L array exhausted, so we're done if R_ONLY isn't set */
			if (!(emit & TSPO_R_ONLY))
				break;
			Lpos = INT_MAX;
		}
		if (Rindex < Rdata->npos)
			Rpos = WEP_GETPOS(Rdata->pos[Rindex]) + Roffset;
		else
		{
			/* R array exhausted, so we're done if L_ONLY isn't set */
			if (!(emit & TSPO_L_ONLY))
				break;
			Rpos = INT_MAX;
		}

		/* Merge-join the two input lists */
		if (Lpos < Rpos)
		{
			/* Lpos is not matched in Rdata, should we output it? */
			if (emit & TSPO_L_ONLY)
				output_pos = Lpos;
			Lindex++;
		}
		else if (Lpos == Rpos)
		{
			/* Lpos and Rpos match ... should we output it? */
			if (emit & TSPO_BOTH)
				output_pos = Rpos;
			Lindex++;
			Rindex++;
		}
		else					/* Lpos > Rpos */
		{
			/* Rpos is not matched in Ldata, should we output it? */
			if (emit & TSPO_R_ONLY)
				output_pos = Rpos;
			Rindex++;
		}

		if (output_pos > 0)
		{
			if (data)
			{
				/* Store position, first allocating output array if needed */
				if (data->pos == NULL)
				{
					data->pos = (WordEntryPos *)
						palloc(max_npos * sizeof(WordEntryPos));
					data->allocated = true;
				}
				data->pos[data->npos++] = output_pos;
			}
			else
			{
				/*
				 * Exact positions not needed, so return true as soon as we
				 * know there is at least one.
				 */
				return true;
			}
		}
	}

	if (data && data->npos > 0)
	{
		/* Let's assert we didn't overrun the array */
		Assert(data->npos <= max_npos);
		return true;
	}
	return false;
}