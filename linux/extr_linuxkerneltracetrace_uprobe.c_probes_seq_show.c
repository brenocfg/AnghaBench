#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* class; } ;
struct TYPE_7__ {int nr_args; TYPE_2__* args; TYPE_4__ call; } ;
struct trace_uprobe {TYPE_3__ tp; int /*<<< orphan*/  offset; int /*<<< orphan*/  filename; } ;
struct seq_file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  system; } ;

/* Variables and functions */
 scalar_t__ is_ret_probe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  trace_event_name (TYPE_4__*) ; 

__attribute__((used)) static int probes_seq_show(struct seq_file *m, void *v)
{
	struct trace_uprobe *tu = v;
	char c = is_ret_probe(tu) ? 'r' : 'p';
	int i;

	seq_printf(m, "%c:%s/%s %s:0x%0*lx", c, tu->tp.call.class->system,
			trace_event_name(&tu->tp.call), tu->filename,
			(int)(sizeof(void *) * 2), tu->offset);

	for (i = 0; i < tu->tp.nr_args; i++)
		seq_printf(m, " %s=%s", tu->tp.args[i].name, tu->tp.args[i].comm);

	seq_putc(m, '\n');
	return 0;
}