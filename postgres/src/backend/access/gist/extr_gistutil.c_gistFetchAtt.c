#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct TYPE_6__ {int /*<<< orphan*/ * supportCollation; int /*<<< orphan*/ * fetchFn; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_1__ GISTSTATE ;
typedef  TYPE_2__ GISTENTRY ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall1Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_2__*) ; 
 int /*<<< orphan*/  gistentryinit (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Datum
gistFetchAtt(GISTSTATE *giststate, int nkey, Datum k, Relation r)
{
	GISTENTRY	fentry;
	GISTENTRY  *fep;

	gistentryinit(fentry, k, r, NULL, (OffsetNumber) 0, false);

	fep = (GISTENTRY *)
		DatumGetPointer(FunctionCall1Coll(&giststate->fetchFn[nkey],
										  giststate->supportCollation[nkey],
										  PointerGetDatum(&fentry)));

	/* fetchFn set 'key', return it to the caller */
	return fep->key;
}