#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct reclaim_state {scalar_t__ reclaimed_slab; } ;
struct alloc_context {int /*<<< orphan*/  nodemask; int /*<<< orphan*/  zonelist; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct reclaim_state* reclaim_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpuset_memory_pressure_bump () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_reclaim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memalloc_noreclaim_restore (unsigned int) ; 
 unsigned int memalloc_noreclaim_save () ; 
 int try_to_free_pages (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__perform_reclaim(gfp_t gfp_mask, unsigned int order,
					const struct alloc_context *ac)
{
	struct reclaim_state reclaim_state;
	int progress;
	unsigned int noreclaim_flag;

	cond_resched();

	/* We now go into synchronous reclaim */
	cpuset_memory_pressure_bump();
	fs_reclaim_acquire(gfp_mask);
	noreclaim_flag = memalloc_noreclaim_save();
	reclaim_state.reclaimed_slab = 0;
	current->reclaim_state = &reclaim_state;

	progress = try_to_free_pages(ac->zonelist, order, gfp_mask,
								ac->nodemask);

	current->reclaim_state = NULL;
	memalloc_noreclaim_restore(noreclaim_flag);
	fs_reclaim_release(gfp_mask);

	cond_resched();

	return progress;
}