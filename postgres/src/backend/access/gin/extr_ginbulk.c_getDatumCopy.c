#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  allocatedMemory; TYPE_1__* ginstate; } ;
struct TYPE_7__ {int /*<<< orphan*/  attlen; scalar_t__ attbyval; } ;
struct TYPE_6__ {int /*<<< orphan*/  origTupdesc; } ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ BuildAccumulator ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMemoryChunkSpace (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
getDatumCopy(BuildAccumulator *accum, OffsetNumber attnum, Datum value)
{
	Form_pg_attribute att;
	Datum		res;

	att = TupleDescAttr(accum->ginstate->origTupdesc, attnum - 1);
	if (att->attbyval)
		res = value;
	else
	{
		res = datumCopy(value, false, att->attlen);
		accum->allocatedMemory += GetMemoryChunkSpace(DatumGetPointer(res));
	}
	return res;
}