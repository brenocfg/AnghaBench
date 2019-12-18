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
struct trace_kprobe {int /*<<< orphan*/  nhit; struct trace_kprobe* symbol; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trace_kprobe*) ; 
 int /*<<< orphan*/  trace_probe_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_trace_kprobe(struct trace_kprobe *tk)
{
	if (tk) {
		trace_probe_cleanup(&tk->tp);
		kfree(tk->symbol);
		free_percpu(tk->nhit);
		kfree(tk);
	}
}