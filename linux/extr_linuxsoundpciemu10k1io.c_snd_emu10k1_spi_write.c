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
struct snd_emu10k1 {int /*<<< orphan*/  spi_lock; TYPE_1__* card_capabilities; } ;
struct TYPE_2__ {scalar_t__ ca0108_chip; } ;

/* Variables and functions */
 unsigned int snd_emu10k1_ptr20_read (struct snd_emu10k1*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr20_write (struct snd_emu10k1*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int snd_emu10k1_spi_write(struct snd_emu10k1 * emu,
				   unsigned int data)
{
	unsigned int reset, set;
	unsigned int reg, tmp;
	int n, result;
	int err = 0;

	/* This function is not re-entrant, so protect against it. */
	spin_lock(&emu->spi_lock);
	if (emu->card_capabilities->ca0108_chip)
		reg = 0x3c; /* PTR20, reg 0x3c */
	else {
		/* For other chip types the SPI register
		 * is currently unknown. */
		err = 1;
		goto spi_write_exit;
	}
	if (data > 0xffff) {
		/* Only 16bit values allowed */
		err = 1;
		goto spi_write_exit;
	}

	tmp = snd_emu10k1_ptr20_read(emu, reg, 0);
	reset = (tmp & ~0x3ffff) | 0x20000; /* Set xxx20000 */
	set = reset | 0x10000; /* Set xxx1xxxx */
	snd_emu10k1_ptr20_write(emu, reg, 0, reset | data);
	tmp = snd_emu10k1_ptr20_read(emu, reg, 0); /* write post */
	snd_emu10k1_ptr20_write(emu, reg, 0, set | data);
	result = 1;
	/* Wait for status bit to return to 0 */
	for (n = 0; n < 100; n++) {
		udelay(10);
		tmp = snd_emu10k1_ptr20_read(emu, reg, 0);
		if (!(tmp & 0x10000)) {
			result = 0;
			break;
		}
	}
	if (result) {
		/* Timed out */
		err = 1;
		goto spi_write_exit;
	}
	snd_emu10k1_ptr20_write(emu, reg, 0, reset | data);
	tmp = snd_emu10k1_ptr20_read(emu, reg, 0); /* Write post */
	err = 0;
spi_write_exit:
	spin_unlock(&emu->spi_lock);
	return err;
}