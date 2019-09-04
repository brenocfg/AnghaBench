#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* class; } ;
struct TYPE_11__ {int nr_args; TYPE_4__* args; TYPE_6__ call; } ;
struct TYPE_8__ {scalar_t__ offset; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_2__ kp; } ;
struct trace_kprobe {TYPE_5__ tp; TYPE_3__ rp; int /*<<< orphan*/  symbol; } ;
struct seq_file {int dummy; } ;
struct TYPE_10__ {scalar_t__ comm; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  system; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 scalar_t__ trace_event_name (TYPE_6__*) ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 
 int /*<<< orphan*/  trace_kprobe_symbol (struct trace_kprobe*) ; 

__attribute__((used)) static int probes_seq_show(struct seq_file *m, void *v)
{
	struct trace_kprobe *tk = v;
	int i;

	seq_putc(m, trace_kprobe_is_return(tk) ? 'r' : 'p');
	seq_printf(m, ":%s/%s", tk->tp.call.class->system,
			trace_event_name(&tk->tp.call));

	if (!tk->symbol)
		seq_printf(m, " 0x%p", tk->rp.kp.addr);
	else if (tk->rp.kp.offset)
		seq_printf(m, " %s+%u", trace_kprobe_symbol(tk),
			   tk->rp.kp.offset);
	else
		seq_printf(m, " %s", trace_kprobe_symbol(tk));

	for (i = 0; i < tk->tp.nr_args; i++)
		seq_printf(m, " %s=%s", tk->tp.args[i].name, tk->tp.args[i].comm);
	seq_putc(m, '\n');

	return 0;
}