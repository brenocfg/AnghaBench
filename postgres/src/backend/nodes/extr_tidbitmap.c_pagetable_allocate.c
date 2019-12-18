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
struct TYPE_6__ {int /*<<< orphan*/  ctx; scalar_t__ private_data; } ;
typedef  TYPE_1__ pagetable_hash ;
struct TYPE_8__ {void* ptentry; } ;
struct TYPE_7__ {int /*<<< orphan*/  dsapagetable; int /*<<< orphan*/ * dsa; int /*<<< orphan*/  dsapagetableold; } ;
typedef  TYPE_2__ TIDBitmap ;
typedef  scalar_t__ Size ;
typedef  TYPE_3__ PTEntryArray ;

/* Variables and functions */
 int DSA_ALLOC_HUGE ; 
 int DSA_ALLOC_ZERO ; 
 int MCXT_ALLOC_HUGE ; 
 int MCXT_ALLOC_ZERO ; 
 void* MemoryContextAllocExtended (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dsa_allocate_extended (int /*<<< orphan*/ *,scalar_t__,int) ; 
 TYPE_3__* dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *
pagetable_allocate(pagetable_hash *pagetable, Size size)
{
	TIDBitmap  *tbm = (TIDBitmap *) pagetable->private_data;
	PTEntryArray *ptbase;

	if (tbm->dsa == NULL)
		return MemoryContextAllocExtended(pagetable->ctx, size,
										  MCXT_ALLOC_HUGE | MCXT_ALLOC_ZERO);

	/*
	 * Save the dsapagetable reference in dsapagetableold before allocating
	 * new memory so that pagetable_free can free the old entry.
	 */
	tbm->dsapagetableold = tbm->dsapagetable;
	tbm->dsapagetable = dsa_allocate_extended(tbm->dsa,
											  sizeof(PTEntryArray) + size,
											  DSA_ALLOC_HUGE | DSA_ALLOC_ZERO);
	ptbase = dsa_get_address(tbm->dsa, tbm->dsapagetable);

	return ptbase->ptentry;
}