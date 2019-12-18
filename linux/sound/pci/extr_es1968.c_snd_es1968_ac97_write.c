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
struct snd_ac97 {struct es1968* private_data; } ;
struct es1968 {scalar_t__ io_port; } ;

/* Variables and functions */
 scalar_t__ ESM_AC97_DATA ; 
 scalar_t__ ESM_AC97_INDEX ; 
 int /*<<< orphan*/  outb (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  snd_es1968_ac97_wait (struct es1968*) ; 

__attribute__((used)) static void snd_es1968_ac97_write(struct snd_ac97 *ac97, unsigned short reg, unsigned short val)
{
	struct es1968 *chip = ac97->private_data;

	snd_es1968_ac97_wait(chip);

	/* Write the bus */
	outw(val, chip->io_port + ESM_AC97_DATA);
	/*msleep(1);*/
	outb(reg, chip->io_port + ESM_AC97_INDEX);
	/*msleep(1);*/
}