#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_11__ {scalar_t__ nallocatable; scalar_t__ nmax; int /*<<< orphan*/  nextspan; } ;
typedef  TYPE_2__ dsa_area_span ;
struct TYPE_12__ {int /*<<< orphan*/ * spans; } ;
typedef  TYPE_3__ dsa_area_pool ;
struct TYPE_13__ {TYPE_1__* control; } ;
typedef  TYPE_4__ dsa_area ;
struct TYPE_10__ {TYPE_3__* pools; } ;

/* Variables and functions */
 int DSA_NUM_SIZE_CLASSES ; 
 int /*<<< orphan*/  DSA_SCLASS_LOCK (TYPE_4__*,int) ; 
 int DSA_SCLASS_SPAN_LARGE ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  destroy_superblock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dsa_get_address (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
dsa_trim(dsa_area *area)
{
	int			size_class;

	/*
	 * Trim in reverse pool order so we get to the spans-of-spans last, just
	 * in case any become entirely free while processing all the other pools.
	 */
	for (size_class = DSA_NUM_SIZE_CLASSES - 1; size_class >= 0; --size_class)
	{
		dsa_area_pool *pool = &area->control->pools[size_class];
		dsa_pointer span_pointer;

		if (size_class == DSA_SCLASS_SPAN_LARGE)
		{
			/* Large object frees give back segments aggressively already. */
			continue;
		}

		/*
		 * Search fullness class 1 only.  That is where we expect to find an
		 * entirely empty superblock (entirely empty superblocks in other
		 * fullness classes are returned to the free page map by dsa_free).
		 */
		LWLockAcquire(DSA_SCLASS_LOCK(area, size_class), LW_EXCLUSIVE);
		span_pointer = pool->spans[1];
		while (DsaPointerIsValid(span_pointer))
		{
			dsa_area_span *span = dsa_get_address(area, span_pointer);
			dsa_pointer next = span->nextspan;

			if (span->nallocatable == span->nmax)
				destroy_superblock(area, span_pointer);

			span_pointer = next;
		}
		LWLockRelease(DSA_SCLASS_LOCK(area, size_class));
	}
}