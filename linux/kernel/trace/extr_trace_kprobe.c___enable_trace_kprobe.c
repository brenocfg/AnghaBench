#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kp; } ;
struct trace_kprobe {TYPE_1__ rp; } ;

/* Variables and functions */
 int enable_kprobe (int /*<<< orphan*/ *) ; 
 int enable_kretprobe (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_kprobe_has_gone (struct trace_kprobe*) ; 
 scalar_t__ trace_kprobe_is_registered (struct trace_kprobe*) ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 

__attribute__((used)) static inline int __enable_trace_kprobe(struct trace_kprobe *tk)
{
	int ret = 0;

	if (trace_kprobe_is_registered(tk) && !trace_kprobe_has_gone(tk)) {
		if (trace_kprobe_is_return(tk))
			ret = enable_kretprobe(&tk->rp);
		else
			ret = enable_kprobe(&tk->rp.kp);
	}

	return ret;
}