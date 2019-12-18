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
typedef  scalar_t__ uint32 ;
struct TYPE_6__ {scalar_t__ maxitems; scalar_t__ nitems; int /*<<< orphan*/  magic; } ;
struct TYPE_5__ {scalar_t__ dsm_control; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ PGShmemHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 scalar_t__ DSM_HANDLE_INVALID ; 
 scalar_t__ DSM_IMPL_MMAP ; 
 int /*<<< orphan*/  DSM_OP_CREATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int MaxBackends ; 
 int /*<<< orphan*/  PG_DYNSHMEM_CONTROL_MAGIC ; 
 scalar_t__ PG_DYNSHMEM_FIXED_SLOTS ; 
 int PG_DYNSHMEM_SLOTS_PER_BACKEND ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  dsm_cleanup_for_mmap () ; 
 TYPE_3__* dsm_control ; 
 int /*<<< orphan*/  dsm_control_bytes_needed (scalar_t__) ; 
 scalar_t__ dsm_control_handle ; 
 int /*<<< orphan*/  dsm_control_impl_private ; 
 scalar_t__ dsm_control_mapped_size ; 
 scalar_t__ dsm_impl_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_postmaster_shutdown ; 
 scalar_t__ dynamic_shared_memory_type ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random () ; 

void
dsm_postmaster_startup(PGShmemHeader *shim)
{
	void	   *dsm_control_address = NULL;
	uint32		maxitems;
	Size		segsize;

	Assert(!IsUnderPostmaster);

	/*
	 * If we're using the mmap implementations, clean up any leftovers.
	 * Cleanup isn't needed on Windows, and happens earlier in startup for
	 * POSIX and System V shared memory, via a direct call to
	 * dsm_cleanup_using_control_segment.
	 */
	if (dynamic_shared_memory_type == DSM_IMPL_MMAP)
		dsm_cleanup_for_mmap();

	/* Determine size for new control segment. */
	maxitems = PG_DYNSHMEM_FIXED_SLOTS
		+ PG_DYNSHMEM_SLOTS_PER_BACKEND * MaxBackends;
	elog(DEBUG2, "dynamic shared memory system will support %u segments",
		 maxitems);
	segsize = dsm_control_bytes_needed(maxitems);

	/*
	 * Loop until we find an unused identifier for the new control segment. We
	 * sometimes use 0 as a sentinel value indicating that no control segment
	 * is known to exist, so avoid using that value for a real control
	 * segment.
	 */
	for (;;)
	{
		Assert(dsm_control_address == NULL);
		Assert(dsm_control_mapped_size == 0);
		dsm_control_handle = random();
		if (dsm_control_handle == DSM_HANDLE_INVALID)
			continue;
		if (dsm_impl_op(DSM_OP_CREATE, dsm_control_handle, segsize,
						&dsm_control_impl_private, &dsm_control_address,
						&dsm_control_mapped_size, ERROR))
			break;
	}
	dsm_control = dsm_control_address;
	on_shmem_exit(dsm_postmaster_shutdown, PointerGetDatum(shim));
	elog(DEBUG2,
		 "created dynamic shared memory control segment %u (%zu bytes)",
		 dsm_control_handle, segsize);
	shim->dsm_control = dsm_control_handle;

	/* Initialize control segment. */
	dsm_control->magic = PG_DYNSHMEM_CONTROL_MAGIC;
	dsm_control->nitems = 0;
	dsm_control->maxitems = maxitems;
}