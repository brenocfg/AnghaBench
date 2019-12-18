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
 unsigned short AC97C_CSR_RXRDY ; 
 unsigned short AC97C_CSR_TXRDY ; 
 int /*<<< orphan*/  CORHR ; 
 int /*<<< orphan*/  COSR ; 
 int /*<<< orphan*/  COTHR ; 
 unsigned short ac97c_readl (struct atmel_ac97c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct atmel_ac97c* get_chip (struct snd_ac97*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short atmel_ac97c_read(struct snd_ac97 *ac97,
		unsigned short reg)
{
	struct atmel_ac97c *chip = get_chip(ac97);
	unsigned long word;
	int timeout = 40;
	int write = 10;

	word = (0x80 | (reg & 0x7f)) << 16;

	if ((ac97c_readl(chip, COSR) & AC97C_CSR_RXRDY) != 0)
		ac97c_readl(chip, CORHR);

retry_write:
	timeout = 40;

	do {
		if ((ac97c_readl(chip, COSR) & AC97C_CSR_TXRDY) != 0) {
			ac97c_writel(chip, COTHR, word);
			goto read_reg;
		}
		udelay(10);
	} while (--timeout);

	if (!--write)
		goto timed_out;
	goto retry_write;

read_reg:
	do {
		if ((ac97c_readl(chip, COSR) & AC97C_CSR_RXRDY) != 0) {
			unsigned short val = ac97c_readl(chip, CORHR);
			return val;
		}
		udelay(10);
	} while (--timeout);

	if (!--write)
		goto timed_out;
	goto retry_write;

timed_out:
	dev_dbg(&chip->pdev->dev, "codec read timeout\n");
	return 0xffff;
}