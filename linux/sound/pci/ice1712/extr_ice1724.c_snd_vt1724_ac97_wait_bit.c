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
 int EIO ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_vt1724_ac97_wait_bit(struct snd_ice1712 *ice, unsigned char bit)
{
	int tm;
	for (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEMT1724(ice, AC97_CMD)) & bit) == 0)
			return 0;
	dev_dbg(ice->card->dev, "snd_vt1724_ac97_wait_bit: timeout\n");
	return -EIO;
}