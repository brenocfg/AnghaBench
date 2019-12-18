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
struct perf_thread_map {int nr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  perf_thread_map__pid (struct perf_thread_map*,int) ; 

size_t thread_map__fprintf(struct perf_thread_map *threads, FILE *fp)
{
	int i;
	size_t printed = fprintf(fp, "%d thread%s: ",
				 threads->nr, threads->nr > 1 ? "s" : "");
	for (i = 0; i < threads->nr; ++i)
		printed += fprintf(fp, "%s%d", i ? ", " : "", perf_thread_map__pid(threads, i));

	return printed + fprintf(fp, "\n");
}