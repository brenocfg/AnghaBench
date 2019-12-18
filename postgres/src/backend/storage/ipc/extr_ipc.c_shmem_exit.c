#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* function ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* function ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG3 ; 
 scalar_t__ before_shmem_exit_index ; 
 TYPE_2__* before_shmem_exit_list ; 
 int /*<<< orphan*/  dsm_backend_shutdown () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 scalar_t__ on_shmem_exit_index ; 
 TYPE_1__* on_shmem_exit_list ; 
 int shmem_exit_inprogress ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 

void
shmem_exit(int code)
{
	shmem_exit_inprogress = true;

	/*
	 * Call before_shmem_exit callbacks.
	 *
	 * These should be things that need most of the system to still be up and
	 * working, such as cleanup of temp relations, which requires catalog
	 * access; or things that need to be completed because later cleanup steps
	 * depend on them, such as releasing lwlocks.
	 */
	elog(DEBUG3, "shmem_exit(%d): %d before_shmem_exit callbacks to make",
		 code, before_shmem_exit_index);
	while (--before_shmem_exit_index >= 0)
		before_shmem_exit_list[before_shmem_exit_index].function(code,
																 before_shmem_exit_list[before_shmem_exit_index].arg);
	before_shmem_exit_index = 0;

	/*
	 * Call dynamic shared memory callbacks.
	 *
	 * These serve the same purpose as late callbacks, but for dynamic shared
	 * memory segments rather than the main shared memory segment.
	 * dsm_backend_shutdown() has the same kind of progressive logic we use
	 * for the main shared memory segment; namely, it unregisters each
	 * callback before invoking it, so that we don't get stuck in an infinite
	 * loop if one of those callbacks itself throws an ERROR or FATAL.
	 *
	 * Note that explicitly calling this function here is quite different from
	 * registering it as an on_shmem_exit callback for precisely this reason:
	 * if one dynamic shared memory callback errors out, the remaining
	 * callbacks will still be invoked.  Thus, hard-coding this call puts it
	 * equal footing with callbacks for the main shared memory segment.
	 */
	dsm_backend_shutdown();

	/*
	 * Call on_shmem_exit callbacks.
	 *
	 * These are generally releasing low-level shared memory resources.  In
	 * some cases, this is a backstop against the possibility that the early
	 * callbacks might themselves fail, leading to re-entry to this routine;
	 * in other cases, it's cleanup that only happens at process exit.
	 */
	elog(DEBUG3, "shmem_exit(%d): %d on_shmem_exit callbacks to make",
		 code, on_shmem_exit_index);
	while (--on_shmem_exit_index >= 0)
		on_shmem_exit_list[on_shmem_exit_index].function(code,
														 on_shmem_exit_list[on_shmem_exit_index].arg);
	on_shmem_exit_index = 0;

	shmem_exit_inprogress = false;
}