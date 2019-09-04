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
typedef  int u32 ;
struct pinctrl_pin_desc {scalar_t__ number; } ;
struct TYPE_2__ {int need_valid_mask; int /*<<< orphan*/  domain; int /*<<< orphan*/  valid_mask; } ;
struct gpio_chip {int base; TYPE_1__ irq; int /*<<< orphan*/  parent; int /*<<< orphan*/  label; scalar_t__ ngpio; } ;
struct chv_pinctrl {int /*<<< orphan*/  dev; scalar_t__ regs; struct chv_community* community; struct gpio_chip chip; } ;
struct chv_gpio_pinrange {scalar_t__ npins; int /*<<< orphan*/  base; } ;
struct chv_community {int npins; int ngpio_ranges; int nirqs; struct chv_gpio_pinrange* gpio_ranges; struct pinctrl_pin_desc* pins; } ;

/* Variables and functions */
 scalar_t__ CHV_INTMASK ; 
 scalar_t__ CHV_INTSTAT ; 
 int /*<<< orphan*/  CHV_PADCTRL0 ; 
 int CHV_PADCTRL0_INTSEL_MASK ; 
 int CHV_PADCTRL0_INTSEL_SHIFT ; 
 int GENMASK (int,int) ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 struct gpio_chip chv_gpio_chip ; 
 int /*<<< orphan*/  chv_gpio_irq_handler ; 
 int /*<<< orphan*/  chv_gpio_irqchip ; 
 int /*<<< orphan*/  chv_no_valid_mask ; 
 int /*<<< orphan*/  chv_padreg (struct chv_pinctrl*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chv_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (int /*<<< orphan*/ ,struct gpio_chip*,struct chv_pinctrl*) ; 
 int devm_irq_alloc_descs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int gpiochip_add_pin_range (struct gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int gpiochip_irqchip_add (struct gpio_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_set_chained_irqchip (struct gpio_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  irq_domain_associate_many (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chv_gpio_probe(struct chv_pinctrl *pctrl, int irq)
{
	const struct chv_gpio_pinrange *range;
	struct gpio_chip *chip = &pctrl->chip;
	bool need_valid_mask = !dmi_check_system(chv_no_valid_mask);
	const struct chv_community *community = pctrl->community;
	int ret, i, irq_base;

	*chip = chv_gpio_chip;

	chip->ngpio = community->pins[community->npins - 1].number + 1;
	chip->label = dev_name(pctrl->dev);
	chip->parent = pctrl->dev;
	chip->base = -1;
	chip->irq.need_valid_mask = need_valid_mask;

	ret = devm_gpiochip_add_data(pctrl->dev, chip, pctrl);
	if (ret) {
		dev_err(pctrl->dev, "Failed to register gpiochip\n");
		return ret;
	}

	for (i = 0; i < community->ngpio_ranges; i++) {
		range = &community->gpio_ranges[i];
		ret = gpiochip_add_pin_range(chip, dev_name(pctrl->dev),
					     range->base, range->base,
					     range->npins);
		if (ret) {
			dev_err(pctrl->dev, "failed to add GPIO pin range\n");
			return ret;
		}
	}

	/* Do not add GPIOs that can only generate GPEs to the IRQ domain */
	for (i = 0; i < community->npins; i++) {
		const struct pinctrl_pin_desc *desc;
		u32 intsel;

		desc = &community->pins[i];

		intsel = readl(chv_padreg(pctrl, desc->number, CHV_PADCTRL0));
		intsel &= CHV_PADCTRL0_INTSEL_MASK;
		intsel >>= CHV_PADCTRL0_INTSEL_SHIFT;

		if (need_valid_mask && intsel >= community->nirqs)
			clear_bit(i, chip->irq.valid_mask);
	}

	/*
	 * The same set of machines in chv_no_valid_mask[] have incorrectly
	 * configured GPIOs that generate spurious interrupts so we use
	 * this same list to apply another quirk for them.
	 *
	 * See also https://bugzilla.kernel.org/show_bug.cgi?id=197953.
	 */
	if (!need_valid_mask) {
		/*
		 * Mask all interrupts the community is able to generate
		 * but leave the ones that can only generate GPEs unmasked.
		 */
		chv_writel(GENMASK(31, pctrl->community->nirqs),
			   pctrl->regs + CHV_INTMASK);
	}

	/* Clear all interrupts */
	chv_writel(0xffff, pctrl->regs + CHV_INTSTAT);

	if (!need_valid_mask) {
		irq_base = devm_irq_alloc_descs(pctrl->dev, -1, 0,
						community->npins, NUMA_NO_NODE);
		if (irq_base < 0) {
			dev_err(pctrl->dev, "Failed to allocate IRQ numbers\n");
			return irq_base;
		}
	}

	ret = gpiochip_irqchip_add(chip, &chv_gpio_irqchip, 0,
				   handle_bad_irq, IRQ_TYPE_NONE);
	if (ret) {
		dev_err(pctrl->dev, "failed to add IRQ chip\n");
		return ret;
	}

	if (!need_valid_mask) {
		for (i = 0; i < community->ngpio_ranges; i++) {
			range = &community->gpio_ranges[i];

			irq_domain_associate_many(chip->irq.domain, irq_base,
						  range->base, range->npins);
			irq_base += range->npins;
		}
	}

	gpiochip_set_chained_irqchip(chip, &chv_gpio_irqchip, irq,
				     chv_gpio_irq_handler);
	return 0;
}