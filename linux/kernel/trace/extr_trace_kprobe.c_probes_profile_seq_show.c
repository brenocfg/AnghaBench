#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nmissed; } ;
struct TYPE_4__ {TYPE_1__ kp; } ;
struct trace_kprobe {TYPE_2__ rp; int /*<<< orphan*/  tp; } ;
struct seq_file {int dummy; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_trace_kprobe (struct dyn_event*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trace_kprobe* to_trace_kprobe (struct dyn_event*) ; 
 int /*<<< orphan*/  trace_kprobe_nhit (struct trace_kprobe*) ; 
 int /*<<< orphan*/  trace_probe_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int probes_profile_seq_show(struct seq_file *m, void *v)
{
	struct dyn_event *ev = v;
	struct trace_kprobe *tk;

	if (!is_trace_kprobe(ev))
		return 0;

	tk = to_trace_kprobe(ev);
	seq_printf(m, "  %-44s %15lu %15lu\n",
		   trace_probe_name(&tk->tp),
		   trace_kprobe_nhit(tk),
		   tk->rp.kp.nmissed);

	return 0;
}