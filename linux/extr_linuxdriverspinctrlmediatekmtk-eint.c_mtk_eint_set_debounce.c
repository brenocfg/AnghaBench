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
struct mtk_eint {scalar_t__ base; TYPE_1__* regs; int /*<<< orphan*/  domain; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {unsigned long dbnc_set; unsigned long dbnc_clr; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int const*) ; 
 int EINVAL ; 
 int MTK_EINT_DBNC_RST_BIT ; 
 unsigned int MTK_EINT_DBNC_SET_DBNC_BITS ; 
 unsigned int MTK_EINT_DBNC_SET_EN ; 
 int irq_find_mapping (int /*<<< orphan*/ ,unsigned long) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 int /*<<< orphan*/  mtk_eint_can_en_debounce (struct mtk_eint*,unsigned long) ; 
 int /*<<< orphan*/  mtk_eint_get_mask (struct mtk_eint*,unsigned long) ; 
 int /*<<< orphan*/  mtk_eint_mask (struct irq_data*) ; 
 int /*<<< orphan*/  mtk_eint_unmask (struct irq_data*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

int mtk_eint_set_debounce(struct mtk_eint *eint, unsigned long eint_num,
			  unsigned int debounce)
{
	int virq, eint_offset;
	unsigned int set_offset, bit, clr_bit, clr_offset, rst, i, unmask,
		     dbnc;
	static const unsigned int debounce_time[] = {500, 1000, 16000, 32000,
						     64000, 128000, 256000};
	struct irq_data *d;

	virq = irq_find_mapping(eint->domain, eint_num);
	eint_offset = (eint_num % 4) * 8;
	d = irq_get_irq_data(virq);

	set_offset = (eint_num / 4) * 4 + eint->regs->dbnc_set;
	clr_offset = (eint_num / 4) * 4 + eint->regs->dbnc_clr;

	if (!mtk_eint_can_en_debounce(eint, eint_num))
		return -EINVAL;

	dbnc = ARRAY_SIZE(debounce_time);
	for (i = 0; i < ARRAY_SIZE(debounce_time); i++) {
		if (debounce <= debounce_time[i]) {
			dbnc = i;
			break;
		}
	}

	if (!mtk_eint_get_mask(eint, eint_num)) {
		mtk_eint_mask(d);
		unmask = 1;
	} else {
		unmask = 0;
	}

	clr_bit = 0xff << eint_offset;
	writel(clr_bit, eint->base + clr_offset);

	bit = ((dbnc << MTK_EINT_DBNC_SET_DBNC_BITS) | MTK_EINT_DBNC_SET_EN) <<
		eint_offset;
	rst = MTK_EINT_DBNC_RST_BIT << eint_offset;
	writel(rst | bit, eint->base + set_offset);

	/*
	 * Delay a while (more than 2T) to wait for hw debounce counter reset
	 * work correctly.
	 */
	udelay(1);
	if (unmask == 1)
		mtk_eint_unmask(d);

	return 0;
}