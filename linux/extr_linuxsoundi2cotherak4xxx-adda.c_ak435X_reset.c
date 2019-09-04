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
struct snd_akm4xxx {unsigned char total_regs; } ;

/* Variables and functions */
 int snd_akm4xxx_get (struct snd_akm4xxx*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_akm4xxx_write (struct snd_akm4xxx*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ak435X_reset(struct snd_akm4xxx *ak, int state)
{
	unsigned char reg;

	if (state) {
		snd_akm4xxx_write(ak, 0, 0x01, 0x02); /* reset and soft-mute */
		return;
	}
	for (reg = 0x00; reg < ak->total_regs; reg++)
		if (reg != 0x01)
			snd_akm4xxx_write(ak, 0, reg,
					  snd_akm4xxx_get(ak, 0, reg));
	snd_akm4xxx_write(ak, 0, 0x01, 0x01); /* un-reset, unmute */
}