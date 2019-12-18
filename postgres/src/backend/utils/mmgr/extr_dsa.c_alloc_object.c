#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dsa_pointer ;
struct TYPE_13__ {scalar_t__ nallocatable; size_t firstfree; size_t ninitialized; scalar_t__ start; } ;
typedef  TYPE_2__ dsa_area_span ;
struct TYPE_14__ {scalar_t__* spans; } ;
typedef  TYPE_3__ dsa_area_pool ;
struct TYPE_15__ {TYPE_1__* control; } ;
typedef  TYPE_4__ dsa_area ;
struct TYPE_12__ {TYPE_3__* pools; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DSA_FULLNESS_CLASSES ; 
 int DSA_NUM_SIZE_CLASSES ; 
 int /*<<< orphan*/  DSA_SCLASS_LOCK (TYPE_4__*,int) ; 
 size_t DSA_SPAN_NOTHING_FREE ; 
 int DsaPointerIsValid (scalar_t__) ; 
 scalar_t__ InvalidDsaPointer ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 size_t NextFreeObjectIndex (char*) ; 
 char* dsa_get_address (TYPE_4__*,scalar_t__) ; 
 size_t* dsa_size_classes ; 
 int /*<<< orphan*/  ensure_active_superblock (TYPE_4__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  transfer_first_span (TYPE_4__*,TYPE_3__*,int,scalar_t__) ; 

__attribute__((used)) static inline dsa_pointer
alloc_object(dsa_area *area, int size_class)
{
	dsa_area_pool *pool = &area->control->pools[size_class];
	dsa_area_span *span;
	dsa_pointer block;
	dsa_pointer result;
	char	   *object;
	size_t		size;

	/*
	 * Even though ensure_active_superblock can in turn call alloc_object if
	 * it needs to allocate a new span, that's always from a different pool,
	 * and the order of lock acquisition is always the same, so it's OK that
	 * we hold this lock for the duration of this function.
	 */
	Assert(!LWLockHeldByMe(DSA_SCLASS_LOCK(area, size_class)));
	LWLockAcquire(DSA_SCLASS_LOCK(area, size_class), LW_EXCLUSIVE);

	/*
	 * If there's no active superblock, we must successfully obtain one or
	 * fail the request.
	 */
	if (!DsaPointerIsValid(pool->spans[1]) &&
		!ensure_active_superblock(area, pool, size_class))
	{
		result = InvalidDsaPointer;
	}
	else
	{
		/*
		 * There should be a block in fullness class 1 at this point, and it
		 * should never be completely full.  Thus we can either pop an object
		 * from the free list or, failing that, initialize a new object.
		 */
		Assert(DsaPointerIsValid(pool->spans[1]));
		span = (dsa_area_span *)
			dsa_get_address(area, pool->spans[1]);
		Assert(span->nallocatable > 0);
		block = span->start;
		Assert(size_class < DSA_NUM_SIZE_CLASSES);
		size = dsa_size_classes[size_class];
		if (span->firstfree != DSA_SPAN_NOTHING_FREE)
		{
			result = block + span->firstfree * size;
			object = dsa_get_address(area, result);
			span->firstfree = NextFreeObjectIndex(object);
		}
		else
		{
			result = block + span->ninitialized * size;
			++span->ninitialized;
		}
		--span->nallocatable;

		/* If it's now full, move it to the highest-numbered fullness class. */
		if (span->nallocatable == 0)
			transfer_first_span(area, pool, 1, DSA_FULLNESS_CLASSES - 1);
	}

	Assert(LWLockHeldByMe(DSA_SCLASS_LOCK(area, size_class)));
	LWLockRelease(DSA_SCLASS_LOCK(area, size_class));

	return result;
}