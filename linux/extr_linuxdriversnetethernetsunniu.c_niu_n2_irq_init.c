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
typedef  int /*<<< orphan*/  u8 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int niu_n2_irq_init(struct niu *np, u8 *ldg_num_map)
{
#ifdef CONFIG_SPARC64
	struct platform_device *op = np->op;
	const u32 *int_prop;
	int i;

	int_prop = of_get_property(op->dev.of_node, "interrupts", NULL);
	if (!int_prop)
		return -ENODEV;

	for (i = 0; i < op->archdata.num_irqs; i++) {
		ldg_num_map[i] = int_prop[i];
		np->ldg[i].irq = op->archdata.irqs[i];
	}

	np->num_ldg = op->archdata.num_irqs;

	return 0;
#else
	return -EINVAL;
#endif
}