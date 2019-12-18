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
struct snd_als300 {scalar_t__ port; } ;
struct snd_ac97 {struct snd_als300* private_data; } ;

/* Variables and functions */
 scalar_t__ AC97_ACCESS ; 
 int AC97_BUSY ; 
 scalar_t__ AC97_STATUS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_als300_ac97_write(struct snd_ac97 *ac97,
				unsigned short reg, unsigned short val)
{
	int i;
	struct snd_als300 *chip = ac97->private_data;

	for (i = 0; i < 1000; i++) {
		if ((inb(chip->port+AC97_STATUS) & (AC97_BUSY)) == 0)
			break;
		udelay(10);
	}
	outl((reg << 24) | val, chip->port+AC97_ACCESS);
}