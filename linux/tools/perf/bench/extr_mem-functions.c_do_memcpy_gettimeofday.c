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
struct timeval {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* memcpy ) (void*,void*,size_t) ;} ;
struct function {TYPE_1__ fn; } ;
typedef  int /*<<< orphan*/  (* memcpy_t ) (void*,void*,size_t) ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int nr_loops ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 double timeval2double (struct timeval*) ; 

__attribute__((used)) static double do_memcpy_gettimeofday(const struct function *r, size_t size, void *src, void *dst)
{
	struct timeval tv_start, tv_end, tv_diff;
	memcpy_t fn = r->fn.memcpy;
	int i;

	/*
	 * We prefault the freshly allocated memory range here,
	 * to not measure page fault overhead:
	 */
	fn(dst, src, size);

	BUG_ON(gettimeofday(&tv_start, NULL));
	for (i = 0; i < nr_loops; ++i)
		fn(dst, src, size);
	BUG_ON(gettimeofday(&tv_end, NULL));

	timersub(&tv_end, &tv_start, &tv_diff);

	return (double)(((double)size * nr_loops) / timeval2double(&tv_diff));
}