#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {TYPE_4__ kp; } ;
struct TYPE_5__ {int nr_args; int /*<<< orphan*/  flags; int /*<<< orphan*/ * args; } ;
struct trace_kprobe {TYPE_3__ rp; TYPE_1__ tp; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  KPROBE_FLAG_DISABLED ; 
 int /*<<< orphan*/  TP_FLAG_REGISTERED ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int register_kprobe (TYPE_4__*) ; 
 int register_kretprobe (TYPE_3__*) ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 
 int /*<<< orphan*/  trace_kprobe_symbol (struct trace_kprobe*) ; 
 scalar_t__ trace_probe_is_enabled (TYPE_1__*) ; 
 scalar_t__ trace_probe_is_registered (TYPE_1__*) ; 
 int /*<<< orphan*/  traceprobe_update_arg (int /*<<< orphan*/ *) ; 
 scalar_t__ within_notrace_func (struct trace_kprobe*) ; 

__attribute__((used)) static int __register_trace_kprobe(struct trace_kprobe *tk)
{
	int i, ret;

	if (trace_probe_is_registered(&tk->tp))
		return -EINVAL;

	if (within_notrace_func(tk)) {
		pr_warn("Could not probe notrace function %s\n",
			trace_kprobe_symbol(tk));
		return -EINVAL;
	}

	for (i = 0; i < tk->tp.nr_args; i++)
		traceprobe_update_arg(&tk->tp.args[i]);

	/* Set/clear disabled flag according to tp->flag */
	if (trace_probe_is_enabled(&tk->tp))
		tk->rp.kp.flags &= ~KPROBE_FLAG_DISABLED;
	else
		tk->rp.kp.flags |= KPROBE_FLAG_DISABLED;

	if (trace_kprobe_is_return(tk))
		ret = register_kretprobe(&tk->rp);
	else
		ret = register_kprobe(&tk->rp.kp);

	if (ret == 0) {
		tk->tp.flags |= TP_FLAG_REGISTERED;
	} else if (ret == -EILSEQ) {
		pr_warn("Probing address(0x%p) is not an instruction boundary.\n",
			tk->rp.kp.addr);
		ret = -EINVAL;
	}
	return ret;
}