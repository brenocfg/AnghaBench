#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_6__ {scalar_t__ tdtypeid; scalar_t__ tdtypmod; } ;
struct TYPE_5__ {scalar_t__ base_typid; scalar_t__ base_typmod; TYPE_3__* tupdesc; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ CompositeIOData ;

/* Variables and functions */
 TYPE_3__* CreateTupleDescCopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeTupleDesc (TYPE_3__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_rowtype_tupdesc (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
update_cached_tupdesc(CompositeIOData *io, MemoryContext mcxt)
{
	if (!io->tupdesc ||
		io->tupdesc->tdtypeid != io->base_typid ||
		io->tupdesc->tdtypmod != io->base_typmod)
	{
		TupleDesc	tupdesc = lookup_rowtype_tupdesc(io->base_typid,
													 io->base_typmod);
		MemoryContext oldcxt;

		if (io->tupdesc)
			FreeTupleDesc(io->tupdesc);

		/* copy tuple desc without constraints into cache memory context */
		oldcxt = MemoryContextSwitchTo(mcxt);
		io->tupdesc = CreateTupleDescCopy(tupdesc);
		MemoryContextSwitchTo(oldcxt);

		ReleaseTupleDesc(tupdesc);
	}
}