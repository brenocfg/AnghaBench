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
typedef  scalar_t__ u64 ;
struct map {scalar_t__ maj; scalar_t__ min; scalar_t__ ino; scalar_t__ ino_generation; int flags; } ;
struct hist_entry {scalar_t__ cpumode; TYPE_3__* mem_info; TYPE_1__* thread; } ;
typedef  int int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  al_addr; struct map* map; } ;
struct TYPE_6__ {TYPE_2__ daddr; } ;
struct TYPE_4__ {scalar_t__ pid_; } ;

/* Variables and functions */
 int MAP_SHARED ; 
 scalar_t__ PERF_RECORD_MISC_KERNEL ; 
 scalar_t__ cl_address (int /*<<< orphan*/ ) ; 

int64_t
sort__dcacheline_cmp(struct hist_entry *left, struct hist_entry *right)
{
	u64 l, r;
	struct map *l_map, *r_map;

	if (!left->mem_info)  return -1;
	if (!right->mem_info) return 1;

	/* group event types together */
	if (left->cpumode > right->cpumode) return -1;
	if (left->cpumode < right->cpumode) return 1;

	l_map = left->mem_info->daddr.map;
	r_map = right->mem_info->daddr.map;

	/* if both are NULL, jump to sort on al_addr instead */
	if (!l_map && !r_map)
		goto addr;

	if (!l_map) return -1;
	if (!r_map) return 1;

	if (l_map->maj > r_map->maj) return -1;
	if (l_map->maj < r_map->maj) return 1;

	if (l_map->min > r_map->min) return -1;
	if (l_map->min < r_map->min) return 1;

	if (l_map->ino > r_map->ino) return -1;
	if (l_map->ino < r_map->ino) return 1;

	if (l_map->ino_generation > r_map->ino_generation) return -1;
	if (l_map->ino_generation < r_map->ino_generation) return 1;

	/*
	 * Addresses with no major/minor numbers are assumed to be
	 * anonymous in userspace.  Sort those on pid then address.
	 *
	 * The kernel and non-zero major/minor mapped areas are
	 * assumed to be unity mapped.  Sort those on address.
	 */

	if ((left->cpumode != PERF_RECORD_MISC_KERNEL) &&
	    (!(l_map->flags & MAP_SHARED)) &&
	    !l_map->maj && !l_map->min && !l_map->ino &&
	    !l_map->ino_generation) {
		/* userspace anonymous */

		if (left->thread->pid_ > right->thread->pid_) return -1;
		if (left->thread->pid_ < right->thread->pid_) return 1;
	}

addr:
	/* al_addr does all the right addr - start + offset calculations */
	l = cl_address(left->mem_info->daddr.al_addr);
	r = cl_address(right->mem_info->daddr.al_addr);

	if (l > r) return -1;
	if (l < r) return 1;

	return 0;
}