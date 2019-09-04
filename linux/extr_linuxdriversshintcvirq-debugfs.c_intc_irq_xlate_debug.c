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
struct seq_file {int dummy; } ;
struct intc_map_entry {int enum_id; struct intc_desc_int* desc; } ;
struct TYPE_2__ {int name; } ;
struct intc_desc_int {TYPE_1__ chip; } ;

/* Variables and functions */
 struct intc_map_entry* intc_irq_xlate_get (int) ; 
 int nr_irqs ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int intc_irq_xlate_debug(struct seq_file *m, void *priv)
{
	int i;

	seq_printf(m, "%-5s  %-7s  %-15s\n", "irq", "enum", "chip name");

	for (i = 1; i < nr_irqs; i++) {
		struct intc_map_entry *entry = intc_irq_xlate_get(i);
		struct intc_desc_int *desc = entry->desc;

		if (!desc)
			continue;

		seq_printf(m, "%5d  ", i);
		seq_printf(m, "0x%05x  ", entry->enum_id);
		seq_printf(m, "%-15s\n", desc->chip.name);
	}

	return 0;
}