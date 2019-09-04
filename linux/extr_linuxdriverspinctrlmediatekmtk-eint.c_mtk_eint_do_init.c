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
struct mtk_eint {int /*<<< orphan*/  irq; int /*<<< orphan*/  domain; TYPE_1__* hw; TYPE_2__* dev; void* dual_edge; void* cur_mask; void* wake_mask; int /*<<< orphan*/ * regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int ports; int ap_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_simple_ops ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtk_eint*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (int,struct mtk_eint*) ; 
 int /*<<< orphan*/  mtk_eint_hw_init (struct mtk_eint*) ; 
 int /*<<< orphan*/  mtk_eint_irq_chip ; 
 int /*<<< orphan*/  mtk_eint_irq_handler ; 
 int /*<<< orphan*/  mtk_generic_eint_regs ; 

int mtk_eint_do_init(struct mtk_eint *eint)
{
	int i;

	/* If clients don't assign a specific regs, let's use generic one */
	if (!eint->regs)
		eint->regs = &mtk_generic_eint_regs;

	eint->wake_mask = devm_kcalloc(eint->dev, eint->hw->ports,
				       sizeof(*eint->wake_mask), GFP_KERNEL);
	if (!eint->wake_mask)
		return -ENOMEM;

	eint->cur_mask = devm_kcalloc(eint->dev, eint->hw->ports,
				      sizeof(*eint->cur_mask), GFP_KERNEL);
	if (!eint->cur_mask)
		return -ENOMEM;

	eint->dual_edge = devm_kcalloc(eint->dev, eint->hw->ap_num,
				       sizeof(int), GFP_KERNEL);
	if (!eint->dual_edge)
		return -ENOMEM;

	eint->domain = irq_domain_add_linear(eint->dev->of_node,
					     eint->hw->ap_num,
					     &irq_domain_simple_ops, NULL);
	if (!eint->domain)
		return -ENOMEM;

	mtk_eint_hw_init(eint);
	for (i = 0; i < eint->hw->ap_num; i++) {
		int virq = irq_create_mapping(eint->domain, i);

		irq_set_chip_and_handler(virq, &mtk_eint_irq_chip,
					 handle_level_irq);
		irq_set_chip_data(virq, eint);
	}

	irq_set_chained_handler_and_data(eint->irq, mtk_eint_irq_handler,
					 eint);

	return 0;
}