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
struct TYPE_4__ {int /*<<< orphan*/ * addr; scalar_t__ symbol_name; int /*<<< orphan*/  list; int /*<<< orphan*/  hlist; } ;
struct TYPE_3__ {TYPE_2__ kp; } ;
struct trace_kprobe {TYPE_1__ rp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_kprobe_is_registered (struct trace_kprobe*) ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 
 int /*<<< orphan*/  unregister_kprobe (TYPE_2__*) ; 
 int /*<<< orphan*/  unregister_kretprobe (TYPE_1__*) ; 

__attribute__((used)) static void __unregister_trace_kprobe(struct trace_kprobe *tk)
{
	if (trace_kprobe_is_registered(tk)) {
		if (trace_kprobe_is_return(tk))
			unregister_kretprobe(&tk->rp);
		else
			unregister_kprobe(&tk->rp.kp);
		/* Cleanup kprobe for reuse and mark it unregistered */
		INIT_HLIST_NODE(&tk->rp.kp.hlist);
		INIT_LIST_HEAD(&tk->rp.kp.list);
		if (tk->rp.kp.symbol_name)
			tk->rp.kp.addr = NULL;
	}
}