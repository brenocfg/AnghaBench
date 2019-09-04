#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct perf_event_mmap_page {scalar_t__ aux_size; int /*<<< orphan*/  aux_offset; } ;
struct auxtrace_mmap_params {int /*<<< orphan*/  offset; int /*<<< orphan*/  prot; scalar_t__ len; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; int /*<<< orphan*/  idx; int /*<<< orphan*/  mask; } ;
struct auxtrace_mmap {int /*<<< orphan*/ * base; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; int /*<<< orphan*/  idx; scalar_t__ prev; scalar_t__ len; int /*<<< orphan*/  mask; void* userpg; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug2 (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int auxtrace_mmap__mmap(struct auxtrace_mmap *mm,
			struct auxtrace_mmap_params *mp,
			void *userpg, int fd)
{
	struct perf_event_mmap_page *pc = userpg;

	WARN_ONCE(mm->base, "Uninitialized auxtrace_mmap\n");

	mm->userpg = userpg;
	mm->mask = mp->mask;
	mm->len = mp->len;
	mm->prev = 0;
	mm->idx = mp->idx;
	mm->tid = mp->tid;
	mm->cpu = mp->cpu;

	if (!mp->len) {
		mm->base = NULL;
		return 0;
	}

#if BITS_PER_LONG != 64 && !defined(HAVE_SYNC_COMPARE_AND_SWAP_SUPPORT)
	pr_err("Cannot use AUX area tracing mmaps\n");
	return -1;
#endif

	pc->aux_offset = mp->offset;
	pc->aux_size = mp->len;

	mm->base = mmap(NULL, mp->len, mp->prot, MAP_SHARED, fd, mp->offset);
	if (mm->base == MAP_FAILED) {
		pr_debug2("failed to mmap AUX area\n");
		mm->base = NULL;
		return -1;
	}

	return 0;
}