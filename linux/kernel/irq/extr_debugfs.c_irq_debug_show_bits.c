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
struct irq_bit_descr {unsigned int mask; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void irq_debug_show_bits(struct seq_file *m, int ind, unsigned int state,
				const struct irq_bit_descr *sd, int size)
{
	int i;

	for (i = 0; i < size; i++, sd++) {
		if (state & sd->mask)
			seq_printf(m, "%*s%s\n", ind + 12, "", sd->name);
	}
}