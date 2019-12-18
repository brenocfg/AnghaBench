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
typedef  int u16 ;
struct snd_ymfpci {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_GPIOFUNCENABLE ; 
 int /*<<< orphan*/  YDSXGR_GPIOOUTCTRL ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ymfpci_set_gpio_out(struct snd_ymfpci *chip, int pin, int enable)
{
	u16 reg;
	unsigned long flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	reg = snd_ymfpci_readw(chip, YDSXGR_GPIOFUNCENABLE);
	reg &= ~(1 << pin);
	reg &= ~(1 << (pin + 8));
	snd_ymfpci_writew(chip, YDSXGR_GPIOFUNCENABLE, reg);
	snd_ymfpci_writew(chip, YDSXGR_GPIOOUTCTRL, enable << pin);
	snd_ymfpci_writew(chip, YDSXGR_GPIOFUNCENABLE, reg | (1 << (pin + 8)));
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	return 0;
}