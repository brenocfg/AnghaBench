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
struct seq_file {struct irq_desc* private; } ;
struct irq_desc {int /*<<< orphan*/  lock; int /*<<< orphan*/  wake_depth; int /*<<< orphan*/  depth; int /*<<< orphan*/  istate; int /*<<< orphan*/  status_use_accessors; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  handle_irq; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_node (struct irq_data*) ; 
 int /*<<< orphan*/  irq_debug_show_bits (struct seq_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_debug_show_data (struct seq_file*,struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_debug_show_masks (struct seq_file*,struct irq_desc*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irqd_get (struct irq_data*) ; 
 int /*<<< orphan*/  irqdata_states ; 
 int /*<<< orphan*/  irqdesc_istates ; 
 int /*<<< orphan*/  irqdesc_states ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int irq_debug_show(struct seq_file *m, void *p)
{
	struct irq_desc *desc = m->private;
	struct irq_data *data;

	raw_spin_lock_irq(&desc->lock);
	data = irq_desc_get_irq_data(desc);
	seq_printf(m, "handler:  %ps\n", desc->handle_irq);
	seq_printf(m, "device:   %s\n", desc->dev_name);
	seq_printf(m, "status:   0x%08x\n", desc->status_use_accessors);
	irq_debug_show_bits(m, 0, desc->status_use_accessors, irqdesc_states,
			    ARRAY_SIZE(irqdesc_states));
	seq_printf(m, "istate:   0x%08x\n", desc->istate);
	irq_debug_show_bits(m, 0, desc->istate, irqdesc_istates,
			    ARRAY_SIZE(irqdesc_istates));
	seq_printf(m, "ddepth:   %u\n", desc->depth);
	seq_printf(m, "wdepth:   %u\n", desc->wake_depth);
	seq_printf(m, "dstate:   0x%08x\n", irqd_get(data));
	irq_debug_show_bits(m, 0, irqd_get(data), irqdata_states,
			    ARRAY_SIZE(irqdata_states));
	seq_printf(m, "node:     %d\n", irq_data_get_node(data));
	irq_debug_show_masks(m, desc);
	irq_debug_show_data(m, data, 0);
	raw_spin_unlock_irq(&desc->lock);
	return 0;
}