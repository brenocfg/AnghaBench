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
struct perf_probe_point {int /*<<< orphan*/  offset; int /*<<< orphan*/  retprobe; int /*<<< orphan*/  line; void* lazy_line; void* function; void* file; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  clear_perf_probe_point (struct perf_probe_point*) ; 
 int /*<<< orphan*/  out_err ; 
 void* strdup_or_goto (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_probe_point__copy(struct perf_probe_point *dst,
				  struct perf_probe_point *src)
{
	dst->file = strdup_or_goto(src->file, out_err);
	dst->function = strdup_or_goto(src->function, out_err);
	dst->lazy_line = strdup_or_goto(src->lazy_line, out_err);
	dst->line = src->line;
	dst->retprobe = src->retprobe;
	dst->offset = src->offset;
	return 0;

out_err:
	clear_perf_probe_point(dst);
	return -ENOMEM;
}