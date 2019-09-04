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
typedef  unsigned short u16 ;
struct snd_ac97 {struct es1968* private_data; } ;
struct es1968 {scalar_t__ io_port; } ;

/* Variables and functions */
 scalar_t__ ESM_AC97_DATA ; 
 scalar_t__ ESM_AC97_INDEX ; 
 unsigned short inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned short,scalar_t__) ; 
 int /*<<< orphan*/  snd_es1968_ac97_wait (struct es1968*) ; 
 int /*<<< orphan*/  snd_es1968_ac97_wait_poll (struct es1968*) ; 

__attribute__((used)) static unsigned short snd_es1968_ac97_read(struct snd_ac97 *ac97, unsigned short reg)
{
	u16 data = 0;
	struct es1968 *chip = ac97->private_data;

	snd_es1968_ac97_wait(chip);

	outb(reg | 0x80, chip->io_port + ESM_AC97_INDEX);
	/*msleep(1);*/

	if (!snd_es1968_ac97_wait_poll(chip)) {
		data = inw(chip->io_port + ESM_AC97_DATA);
		/*msleep(1);*/
	}

	return data;
}