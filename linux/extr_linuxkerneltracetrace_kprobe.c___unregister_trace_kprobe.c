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
struct TYPE_5__ {int /*<<< orphan*/ * addr; scalar_t__ symbol_name; } ;
struct TYPE_4__ {TYPE_2__ kp; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct trace_kprobe {TYPE_1__ rp; TYPE_3__ tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_FLAG_REGISTERED ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 
 scalar_t__ trace_probe_is_registered (TYPE_3__*) ; 
 int /*<<< orphan*/  unregister_kprobe (TYPE_2__*) ; 
 int /*<<< orphan*/  unregister_kretprobe (TYPE_1__*) ; 

__attribute__((used)) static void __unregister_trace_kprobe(struct trace_kprobe *tk)
{
	if (trace_probe_is_registered(&tk->tp)) {
		if (trace_kprobe_is_return(tk))
			unregister_kretprobe(&tk->rp);
		else
			unregister_kprobe(&tk->rp.kp);
		tk->tp.flags &= ~TP_FLAG_REGISTERED;
		/* Cleanup kprobe for reuse */
		if (tk->rp.kp.symbol_name)
			tk->rp.kp.addr = NULL;
	}
}