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
struct snd_ac97 {int dummy; } ;
struct atmel_ac97c {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AC97C_CSR_TXRDY ; 
 int /*<<< orphan*/  COSR ; 
 int /*<<< orphan*/  COTHR ; 
 int ac97c_readl (struct atmel_ac97c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct atmel_ac97c* get_chip (struct snd_ac97*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void atmel_ac97c_write(struct snd_ac97 *ac97, unsigned short reg,
		unsigned short val)
{
	struct atmel_ac97c *chip = get_chip(ac97);
	unsigned long word;
	int timeout = 40;

	word = (reg & 0x7f) << 16 | val;

	do {
		if (ac97c_readl(chip, COSR) & AC97C_CSR_TXRDY) {
			ac97c_writel(chip, COTHR, word);
			return;
		}
		udelay(1);
	} while (--timeout);

	dev_dbg(&chip->pdev->dev, "codec write timeout\n");
}