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
typedef  scalar_t__ u64 ;
struct function {char* name; char* desc; } ;
struct bench_mem_info {double (* do_gettimeofday ) (struct function const*,size_t,void*,void*) ;scalar_t__ (* do_cycles ) (struct function const*,size_t,void*,void*) ;scalar_t__ alloc_src; struct function* functions; } ;

/* Variables and functions */
#define  BENCH_FORMAT_DEFAULT 129 
#define  BENCH_FORMAT_SIMPLE 128 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int bench_format ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  print_bps (double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* size_str ; 
 scalar_t__ stub1 (struct function const*,size_t,void*,void*) ; 
 double stub2 (struct function const*,size_t,void*,void*) ; 
 scalar_t__ use_cycles ; 
 void* zalloc (size_t) ; 

__attribute__((used)) static void __bench_mem_function(struct bench_mem_info *info, int r_idx, size_t size, double size_total)
{
	const struct function *r = &info->functions[r_idx];
	double result_bps = 0.0;
	u64 result_cycles = 0;
	void *src = NULL, *dst = zalloc(size);

	printf("# function '%s' (%s)\n", r->name, r->desc);

	if (dst == NULL)
		goto out_alloc_failed;

	if (info->alloc_src) {
		src = zalloc(size);
		if (src == NULL)
			goto out_alloc_failed;
	}

	if (bench_format == BENCH_FORMAT_DEFAULT)
		printf("# Copying %s bytes ...\n\n", size_str);

	if (use_cycles) {
		result_cycles = info->do_cycles(r, size, src, dst);
	} else {
		result_bps = info->do_gettimeofday(r, size, src, dst);
	}

	switch (bench_format) {
	case BENCH_FORMAT_DEFAULT:
		if (use_cycles) {
			printf(" %14lf cycles/byte\n", (double)result_cycles/size_total);
		} else {
			print_bps(result_bps);
		}
		break;

	case BENCH_FORMAT_SIMPLE:
		if (use_cycles) {
			printf("%lf\n", (double)result_cycles/size_total);
		} else {
			printf("%lf\n", result_bps);
		}
		break;

	default:
		BUG_ON(1);
		break;
	}

out_free:
	free(src);
	free(dst);
	return;
out_alloc_failed:
	printf("# Memory allocation failed - maybe size (%s) is too large?\n", size_str);
	goto out_free;
}