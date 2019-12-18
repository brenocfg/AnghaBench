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
struct perf_thread_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __T_OK ; 
 int /*<<< orphan*/  __T_START ; 
 int /*<<< orphan*/  libperf_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libperf_print ; 
 int /*<<< orphan*/  perf_thread_map__get (struct perf_thread_map*) ; 
 struct perf_thread_map* perf_thread_map__new_dummy () ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 

int main(int argc, char **argv)
{
	struct perf_thread_map *threads;

	__T_START;

	libperf_init(libperf_print);

	threads = perf_thread_map__new_dummy();
	if (!threads)
		return -1;

	perf_thread_map__get(threads);
	perf_thread_map__put(threads);
	perf_thread_map__put(threads);

	__T_OK;
	return 0;
}