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
typedef  int /*<<< orphan*/  u64 ;
struct trace {scalar_t__ show_duration; scalar_t__ show_tstamp; } ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fprintf_duration (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 size_t trace__fprintf_comm_tid (struct trace*,struct thread*,int /*<<< orphan*/ *) ; 
 size_t trace__fprintf_tstamp (struct trace*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t trace__fprintf_entry_head(struct trace *trace, struct thread *thread,
					u64 duration, bool duration_calculated, u64 tstamp, FILE *fp)
{
	size_t printed = 0;

	if (trace->show_tstamp)
		printed = trace__fprintf_tstamp(trace, tstamp, fp);
	if (trace->show_duration)
		printed += fprintf_duration(duration, duration_calculated, fp);
	return printed + trace__fprintf_comm_tid(trace, thread, fp);
}