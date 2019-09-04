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
struct snd_akm4xxx {int num_chips; } ;

/* Variables and functions */
 unsigned char snd_akm4xxx_get (struct snd_akm4xxx*,int,unsigned char) ; 
 int /*<<< orphan*/  snd_akm4xxx_write (struct snd_akm4xxx*,int,unsigned char,unsigned char) ; 

__attribute__((used)) static void qtet_akm_set_regs(struct snd_akm4xxx *ak, unsigned char addr,
		unsigned char mask, unsigned char value)
{
	unsigned char tmp;
	int chip;
	for (chip = 0; chip < ak->num_chips; chip++) {
		tmp = snd_akm4xxx_get(ak, chip, addr);
		/* clear the bits */
		tmp &= ~mask;
		/* set the new bits */
		tmp |= value;
		snd_akm4xxx_write(ak, chip, addr, tmp);
	}
}