#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* tts_isnull; int /*<<< orphan*/ * tts_values; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_13__ {int* jf_cleanMap; TYPE_1__* jf_resultSlot; TYPE_2__* jf_cleanTupType; } ;
struct TYPE_12__ {int natts; } ;
typedef  TYPE_3__ JunkFilter ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (TYPE_1__*) ; 
 TYPE_1__* ExecStoreVirtualTuple (TYPE_1__*) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 

TupleTableSlot *
ExecFilterJunk(JunkFilter *junkfilter, TupleTableSlot *slot)
{
	TupleTableSlot *resultSlot;
	AttrNumber *cleanMap;
	TupleDesc	cleanTupType;
	int			cleanLength;
	int			i;
	Datum	   *values;
	bool	   *isnull;
	Datum	   *old_values;
	bool	   *old_isnull;

	/*
	 * Extract all the values of the old tuple.
	 */
	slot_getallattrs(slot);
	old_values = slot->tts_values;
	old_isnull = slot->tts_isnull;

	/*
	 * get info from the junk filter
	 */
	cleanTupType = junkfilter->jf_cleanTupType;
	cleanLength = cleanTupType->natts;
	cleanMap = junkfilter->jf_cleanMap;
	resultSlot = junkfilter->jf_resultSlot;

	/*
	 * Prepare to build a virtual result tuple.
	 */
	ExecClearTuple(resultSlot);
	values = resultSlot->tts_values;
	isnull = resultSlot->tts_isnull;

	/*
	 * Transpose data into proper fields of the new tuple.
	 */
	for (i = 0; i < cleanLength; i++)
	{
		int			j = cleanMap[i];

		if (j == 0)
		{
			values[i] = (Datum) 0;
			isnull[i] = true;
		}
		else
		{
			values[i] = old_values[j - 1];
			isnull[i] = old_isnull[j - 1];
		}
	}

	/*
	 * And return the virtual tuple.
	 */
	return ExecStoreVirtualTuple(resultSlot);
}