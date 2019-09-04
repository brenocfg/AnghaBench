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
struct snd_ca0106 {int dummy; } ;

/* Variables and functions */
 unsigned int SPI ; 
 unsigned int snd_ca0106_ptr_read (struct snd_ca0106*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ca0106_ptr_write (struct snd_ca0106*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int snd_ca0106_spi_write(struct snd_ca0106 * emu,
				   unsigned int data)
{
	unsigned int reset, set;
	unsigned int reg, tmp;
	int n, result;
	reg = SPI;
	if (data > 0xffff) /* Only 16bit values allowed */
		return 1;
	tmp = snd_ca0106_ptr_read(emu, reg, 0);
	reset = (tmp & ~0x3ffff) | 0x20000; /* Set xxx20000 */
	set = reset | 0x10000; /* Set xxx1xxxx */
	snd_ca0106_ptr_write(emu, reg, 0, reset | data);
	tmp = snd_ca0106_ptr_read(emu, reg, 0); /* write post */
	snd_ca0106_ptr_write(emu, reg, 0, set | data);
	result = 1;
	/* Wait for status bit to return to 0 */
	for (n = 0; n < 100; n++) {
		udelay(10);
		tmp = snd_ca0106_ptr_read(emu, reg, 0);
		if (!(tmp & 0x10000)) {
			result = 0;
			break;
		}
	}
	if (result) /* Timed out */
		return 1;
	snd_ca0106_ptr_write(emu, reg, 0, reset | data);
	tmp = snd_ca0106_ptr_read(emu, reg, 0); /* Write post */
	return 0;
}