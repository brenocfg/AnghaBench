#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_13__ {int size; } ;
struct TYPE_12__ {int maxdepth; } ;
typedef  TYPE_1__ TSVectorStat ;
typedef  TYPE_2__* TSVector ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 TYPE_2__* DatumGetTSVector (int /*<<< orphan*/ ) ; 
 TYPE_1__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chooseNextStatEntry (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  insertStatEntry (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 

__attribute__((used)) static TSVectorStat *
ts_accum(MemoryContext persistentContext, TSVectorStat *stat, Datum data)
{
	TSVector	txt = DatumGetTSVector(data);
	uint32		i,
				nbit = 0,
				offset;

	if (stat == NULL)
	{							/* Init in first */
		stat = MemoryContextAllocZero(persistentContext, sizeof(TSVectorStat));
		stat->maxdepth = 1;
	}

	/* simple check of correctness */
	if (txt == NULL || txt->size == 0)
	{
		if (txt && txt != (TSVector) DatumGetPointer(data))
			pfree(txt);
		return stat;
	}

	i = txt->size - 1;
	for (; i > 0; i >>= 1)
		nbit++;

	nbit = 1 << nbit;
	offset = (nbit - txt->size) / 2;

	insertStatEntry(persistentContext, stat, txt, (nbit >> 1) - offset);
	chooseNextStatEntry(persistentContext, stat, txt, 0, nbit, offset);

	return stat;
}