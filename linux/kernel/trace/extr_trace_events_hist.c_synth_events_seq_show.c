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
struct seq_file {int dummy; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 int __synth_event_show (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_synth_event (struct dyn_event*) ; 
 int /*<<< orphan*/  to_synth_event (struct dyn_event*) ; 

__attribute__((used)) static int synth_events_seq_show(struct seq_file *m, void *v)
{
	struct dyn_event *ev = v;

	if (!is_synth_event(ev))
		return 0;

	return __synth_event_show(m, to_synth_event(ev));
}