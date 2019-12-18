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
struct snd_ice1712 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char VT1724_AC97_READ ; 
 unsigned char VT1724_AC97_READY ; 
 unsigned char VT1724_AC97_WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char snd_vt1724_ac97_ready(struct snd_ice1712 *ice)
{
	unsigned char old_cmd;
	int tm;
	for (tm = 0; tm < 0x10000; tm++) {
		old_cmd = inb(ICEMT1724(ice, AC97_CMD));
		if (old_cmd & (VT1724_AC97_WRITE | VT1724_AC97_READ))
			continue;
		if (!(old_cmd & VT1724_AC97_READY))
			continue;
		return old_cmd;
	}
	dev_dbg(ice->card->dev, "snd_vt1724_ac97_ready: timeout\n");
	return old_cmd;
}