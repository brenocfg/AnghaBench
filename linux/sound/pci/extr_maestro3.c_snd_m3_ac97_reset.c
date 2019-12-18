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
typedef  int u16 ;
struct snd_m3 {int iobase; TYPE_1__* card; int /*<<< orphan*/  irda_workaround; scalar_t__ allegro_flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ GPIO_DATA ; 
 scalar_t__ GPIO_DIRECTION ; 
 scalar_t__ GPIO_MASK ; 
 int GPO_PRIMARY_AC97 ; 
 int IO_SRAM_ENABLE ; 
 int LAC_SDFS_ENABLE ; 
 int RAC_SDFS_ENABLE ; 
 scalar_t__ RING_BUS_CTRL_A ; 
 int SERIAL_AC_LINK_ENABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_remote_codec_config (struct snd_m3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_try_read_vendor (struct snd_m3*) ; 
 int tmp ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_m3_ac97_reset(struct snd_m3 *chip)
{
	u16 dir;
	int delay1 = 0, delay2 = 0, i;
	int io = chip->iobase;

	if (chip->allegro_flag) {
		/*
		 * the onboard codec on the allegro seems 
		 * to want to wait a very long time before
		 * coming back to life 
		 */
		delay1 = 50;
		delay2 = 800;
	} else {
		/* maestro3 */
		delay1 = 20;
		delay2 = 500;
	}

	for (i = 0; i < 5; i++) {
		dir = inw(io + GPIO_DIRECTION);
		if (!chip->irda_workaround)
			dir |= 0x10; /* assuming pci bus master? */

		snd_m3_remote_codec_config(chip, 0);

		outw(IO_SRAM_ENABLE, io + RING_BUS_CTRL_A);
		udelay(20);

		outw(dir & ~GPO_PRIMARY_AC97 , io + GPIO_DIRECTION);
		outw(~GPO_PRIMARY_AC97 , io + GPIO_MASK);
		outw(0, io + GPIO_DATA);
		outw(dir | GPO_PRIMARY_AC97, io + GPIO_DIRECTION);

		schedule_timeout_uninterruptible(msecs_to_jiffies(delay1));

		outw(GPO_PRIMARY_AC97, io + GPIO_DATA);
		udelay(5);
		/* ok, bring back the ac-link */
		outw(IO_SRAM_ENABLE | SERIAL_AC_LINK_ENABLE, io + RING_BUS_CTRL_A);
		outw(~0, io + GPIO_MASK);

		schedule_timeout_uninterruptible(msecs_to_jiffies(delay2));

		if (! snd_m3_try_read_vendor(chip))
			break;

		delay1 += 10;
		delay2 += 100;

		dev_dbg(chip->card->dev,
			"retrying codec reset with delays of %d and %d ms\n",
			   delay1, delay2);
	}

#if 0
	/* more gung-ho reset that doesn't
	 * seem to work anywhere :)
	 */
	tmp = inw(io + RING_BUS_CTRL_A);
	outw(RAC_SDFS_ENABLE|LAC_SDFS_ENABLE, io + RING_BUS_CTRL_A);
	msleep(20);
	outw(tmp, io + RING_BUS_CTRL_A);
	msleep(50);
#endif
}