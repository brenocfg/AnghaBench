#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_9__ {int /*<<< orphan*/ * bd_disktdesc; TYPE_3__** bd_info; TYPE_1__* bd_tupdesc; int /*<<< orphan*/  bd_totalstored; int /*<<< orphan*/  bd_context; } ;
struct TYPE_8__ {int oi_nstored; TYPE_2__** oi_typcache; } ;
struct TYPE_7__ {int /*<<< orphan*/  type_id; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_4__ BrinDesc ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateTemplateTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleDesc
brtuple_disk_tupdesc(BrinDesc *brdesc)
{
	/* We cache these in the BrinDesc */
	if (brdesc->bd_disktdesc == NULL)
	{
		int			i;
		int			j;
		AttrNumber	attno = 1;
		TupleDesc	tupdesc;
		MemoryContext oldcxt;

		/* make sure it's in the bdesc's context */
		oldcxt = MemoryContextSwitchTo(brdesc->bd_context);

		tupdesc = CreateTemplateTupleDesc(brdesc->bd_totalstored);

		for (i = 0; i < brdesc->bd_tupdesc->natts; i++)
		{
			for (j = 0; j < brdesc->bd_info[i]->oi_nstored; j++)
				TupleDescInitEntry(tupdesc, attno++, NULL,
								   brdesc->bd_info[i]->oi_typcache[j]->type_id,
								   -1, 0);
		}

		MemoryContextSwitchTo(oldcxt);

		brdesc->bd_disktdesc = tupdesc;
	}

	return brdesc->bd_disktdesc;
}