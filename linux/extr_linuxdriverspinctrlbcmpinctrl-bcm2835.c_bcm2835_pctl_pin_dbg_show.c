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
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct gpio_chip {TYPE_1__ irq; } ;
struct bcm2835_pinctrl {size_t* irq_type; struct gpio_chip gpio_chip; } ;
typedef  enum bcm2835_fsel { ____Placeholder_bcm2835_fsel } bcm2835_fsel ;

/* Variables and functions */
 int /*<<< orphan*/  GPLEV0 ; 
 char** bcm2835_functions ; 
 int bcm2835_gpio_get_bit (struct bcm2835_pinctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 int bcm2835_pinctrl_fsel_get (struct bcm2835_pinctrl*,unsigned int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * irq_type_names ; 
 struct bcm2835_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_pctl_pin_dbg_show(struct pinctrl_dev *pctldev,
		struct seq_file *s,
		unsigned offset)
{
	struct bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	struct gpio_chip *chip = &pc->gpio_chip;
	enum bcm2835_fsel fsel = bcm2835_pinctrl_fsel_get(pc, offset);
	const char *fname = bcm2835_functions[fsel];
	int value = bcm2835_gpio_get_bit(pc, GPLEV0, offset);
	int irq = irq_find_mapping(chip->irq.domain, offset);

	seq_printf(s, "function %s in %s; irq %d (%s)",
		fname, value ? "hi" : "lo",
		irq, irq_type_names[pc->irq_type[offset]]);
}