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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_6__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_5__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  schunks; int /*<<< orphan*/  spages; int /*<<< orphan*/  pagetable; } ;
typedef  TYPE_1__ TBMSharedIteratorState ;
typedef  TYPE_2__ PTIterationArray ;
typedef  TYPE_3__ PTEntryArray ;

/* Variables and functions */
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_atomic_sub_fetch_u32 (int /*<<< orphan*/ *,int) ; 

void
tbm_free_shared_area(dsa_area *dsa, dsa_pointer dp)
{
	TBMSharedIteratorState *istate = dsa_get_address(dsa, dp);
	PTEntryArray *ptbase;
	PTIterationArray *ptpages;
	PTIterationArray *ptchunks;

	if (DsaPointerIsValid(istate->pagetable))
	{
		ptbase = dsa_get_address(dsa, istate->pagetable);
		if (pg_atomic_sub_fetch_u32(&ptbase->refcount, 1) == 0)
			dsa_free(dsa, istate->pagetable);
	}
	if (DsaPointerIsValid(istate->spages))
	{
		ptpages = dsa_get_address(dsa, istate->spages);
		if (pg_atomic_sub_fetch_u32(&ptpages->refcount, 1) == 0)
			dsa_free(dsa, istate->spages);
	}
	if (DsaPointerIsValid(istate->schunks))
	{
		ptchunks = dsa_get_address(dsa, istate->schunks);
		if (pg_atomic_sub_fetch_u32(&ptchunks->refcount, 1) == 0)
			dsa_free(dsa, istate->schunks);
	}

	dsa_free(dsa, dp);
}