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
struct perf_ftrace {TYPE_1__* evlist; int /*<<< orphan*/  target; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/ * map; } ;
struct TYPE_5__ {TYPE_3__* threads; } ;
struct TYPE_4__ {TYPE_2__ core; } ;

/* Variables and functions */
 scalar_t__ append_tracing_file (char*,char*) ; 
 int perf_thread_map__nr (TYPE_3__*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ target__has_cpu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_tracing_pid(struct perf_ftrace *ftrace)
{
	int i;
	char buf[16];

	if (target__has_cpu(&ftrace->target))
		return 0;

	for (i = 0; i < perf_thread_map__nr(ftrace->evlist->core.threads); i++) {
		scnprintf(buf, sizeof(buf), "%d",
			  ftrace->evlist->core.threads->map[i]);
		if (append_tracing_file("set_ftrace_pid", buf) < 0)
			return -1;
	}
	return 0;
}