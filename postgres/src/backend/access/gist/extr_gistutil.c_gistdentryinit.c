#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_9__ {int leafkey; int /*<<< orphan*/  offset; int /*<<< orphan*/  page; int /*<<< orphan*/  rel; int /*<<< orphan*/  key; } ;
struct TYPE_8__ {int /*<<< orphan*/ * supportCollation; TYPE_7__* decompressFn; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_1__ GISTSTATE ;
typedef  TYPE_2__ GISTENTRY ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1Coll (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_2__*) ; 
 int /*<<< orphan*/  gistentryinit (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
gistdentryinit(GISTSTATE *giststate, int nkey, GISTENTRY *e,
			   Datum k, Relation r, Page pg, OffsetNumber o,
			   bool l, bool isNull)
{
	if (!isNull)
	{
		GISTENTRY  *dep;

		gistentryinit(*e, k, r, pg, o, l);

		/* there may not be a decompress function in opclass */
		if (!OidIsValid(giststate->decompressFn[nkey].fn_oid))
			return;

		dep = (GISTENTRY *)
			DatumGetPointer(FunctionCall1Coll(&giststate->decompressFn[nkey],
											  giststate->supportCollation[nkey],
											  PointerGetDatum(e)));
		/* decompressFn may just return the given pointer */
		if (dep != e)
			gistentryinit(*e, dep->key, dep->rel, dep->page, dep->offset,
						  dep->leafkey);
	}
	else
		gistentryinit(*e, (Datum) 0, r, pg, o, l);
}