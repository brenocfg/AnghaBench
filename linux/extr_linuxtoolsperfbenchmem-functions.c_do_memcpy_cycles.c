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
typedef  unsigned long long u64 ;
struct TYPE_2__ {int /*<<< orphan*/  (* memcpy ) (void*,void*,size_t) ;} ;
struct function {TYPE_1__ fn; } ;
typedef  int /*<<< orphan*/  (* memcpy_t ) (void*,void*,size_t) ;

/* Variables and functions */
 unsigned long long get_cycles () ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int nr_loops ; 

__attribute__((used)) static u64 do_memcpy_cycles(const struct function *r, size_t size, void *src, void *dst)
{
	u64 cycle_start = 0ULL, cycle_end = 0ULL;
	memcpy_t fn = r->fn.memcpy;
	int i;

	/* Make sure to always prefault zero pages even if MMAP_THRESH is crossed: */
	memset(src, 0, size);

	/*
	 * We prefault the freshly allocated memory range here,
	 * to not measure page fault overhead:
	 */
	fn(dst, src, size);

	cycle_start = get_cycles();
	for (i = 0; i < nr_loops; ++i)
		fn(dst, src, size);
	cycle_end = get_cycles();

	return cycle_end - cycle_start;
}