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
struct seq_file {int dummy; } ;
struct irq_data {struct irq_data* parent_data; TYPE_2__* domain; int /*<<< orphan*/  hwirq; } ;
struct TYPE_4__ {char* name; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* debug_show ) (struct seq_file*,int /*<<< orphan*/ *,struct irq_data*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  irq_debug_show_chip (struct seq_file*,struct irq_data*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct seq_file*,int /*<<< orphan*/ *,struct irq_data*,int) ; 

__attribute__((used)) static void
irq_debug_show_data(struct seq_file *m, struct irq_data *data, int ind)
{
	seq_printf(m, "%*sdomain:  %s\n", ind, "",
		   data->domain ? data->domain->name : "");
	seq_printf(m, "%*shwirq:   0x%lx\n", ind + 1, "", data->hwirq);
	irq_debug_show_chip(m, data, ind + 1);
	if (data->domain && data->domain->ops && data->domain->ops->debug_show)
		data->domain->ops->debug_show(m, NULL, data, ind + 1);
#ifdef	CONFIG_IRQ_DOMAIN_HIERARCHY
	if (!data->parent_data)
		return;
	seq_printf(m, "%*sparent:\n", ind + 1, "");
	irq_debug_show_data(m, data->parent_data, ind + 4);
#endif
}