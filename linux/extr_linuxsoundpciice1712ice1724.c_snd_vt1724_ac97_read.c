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
struct snd_ice1712 {int dummy; } ;
struct snd_ac97 {unsigned char num; struct snd_ice1712* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 int /*<<< orphan*/  AC97_DATA ; 
 int /*<<< orphan*/  AC97_INDEX ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char VT1724_AC97_ID_MASK ; 
 unsigned char VT1724_AC97_READ ; 
 unsigned short inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 unsigned char snd_vt1724_ac97_ready (struct snd_ice1712*) ; 
 scalar_t__ snd_vt1724_ac97_wait_bit (struct snd_ice1712*,unsigned char) ; 

__attribute__((used)) static unsigned short snd_vt1724_ac97_read(struct snd_ac97 *ac97, unsigned short reg)
{
	struct snd_ice1712 *ice = ac97->private_data;
	unsigned char old_cmd;

	old_cmd = snd_vt1724_ac97_ready(ice);
	old_cmd &= ~VT1724_AC97_ID_MASK;
	old_cmd |= ac97->num;
	outb(reg, ICEMT1724(ice, AC97_INDEX));
	outb(old_cmd | VT1724_AC97_READ, ICEMT1724(ice, AC97_CMD));
	if (snd_vt1724_ac97_wait_bit(ice, VT1724_AC97_READ) < 0)
		return ~0;
	return inw(ICEMT1724(ice, AC97_DATA));
}