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
struct trace {int /*<<< orphan*/  output; int /*<<< orphan*/ * current; scalar_t__ failure_only; } ;
struct thread_trace {int entry_pending; char* entry_str; int /*<<< orphan*/  entry_time; } ;

/* Variables and functions */
 scalar_t__ fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct thread_trace* thread__priv (int /*<<< orphan*/ *) ; 
 size_t trace__fprintf_entry_head (struct trace*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trace__printf_interrupted_entry(struct trace *trace)
{
	struct thread_trace *ttrace;
	size_t printed;

	if (trace->failure_only || trace->current == NULL)
		return 0;

	ttrace = thread__priv(trace->current);

	if (!ttrace->entry_pending)
		return 0;

	printed  = trace__fprintf_entry_head(trace, trace->current, 0, false, ttrace->entry_time, trace->output);
	printed += fprintf(trace->output, "%-70s) ...\n", ttrace->entry_str);
	ttrace->entry_pending = false;

	return printed;
}