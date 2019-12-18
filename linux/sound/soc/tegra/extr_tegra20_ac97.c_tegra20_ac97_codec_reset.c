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
typedef  int u32 ;
struct snd_ac97 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA20_AC97_STATUS1 ; 
 int TEGRA20_AC97_STATUS1_CODEC1_RDY ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 TYPE_1__* workdata ; 

__attribute__((used)) static void tegra20_ac97_codec_reset(struct snd_ac97 *ac97)
{
	u32 readback;
	unsigned long timeout;

	/* reset line is not driven by DAC pad group, have to toggle GPIO */
	gpio_set_value(workdata->reset_gpio, 0);
	udelay(2);

	gpio_set_value(workdata->reset_gpio, 1);
	udelay(2);

	timeout = jiffies + msecs_to_jiffies(100);

	do {
		regmap_read(workdata->regmap, TEGRA20_AC97_STATUS1, &readback);
		if (readback & TEGRA20_AC97_STATUS1_CODEC1_RDY)
			break;
		usleep_range(1000, 2000);
	} while (!time_after(jiffies, timeout));
}