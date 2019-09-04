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
struct irq_data {struct irq_chip* chip; } ;
struct irq_chip {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_debug_show_bits (struct seq_file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqchip_flags ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void
irq_debug_show_chip(struct seq_file *m, struct irq_data *data, int ind)
{
	struct irq_chip *chip = data->chip;

	if (!chip) {
		seq_printf(m, "chip: None\n");
		return;
	}
	seq_printf(m, "%*schip:    %s\n", ind, "", chip->name);
	seq_printf(m, "%*sflags:   0x%lx\n", ind + 1, "", chip->flags);
	irq_debug_show_bits(m, ind, chip->flags, irqchip_flags,
			    ARRAY_SIZE(irqchip_flags));
}