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
struct snd_ac97 {int dummy; } ;
struct ep93xx_ac97_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97EOI ; 
 int AC97EOI_CODECREADY ; 
 int AC97EOI_WINT ; 
 int /*<<< orphan*/  AC97GCR ; 
 int AC97GCR_AC97IFE ; 
 int /*<<< orphan*/  AC97IM ; 
 int /*<<< orphan*/  AC97RESET ; 
 int AC97RESET_TIMEDRESET ; 
 int AC97_CODECREADY ; 
 int /*<<< orphan*/  AC97_TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct ep93xx_ac97_info* ep93xx_ac97_info ; 
 int /*<<< orphan*/  ep93xx_ac97_write_reg (struct ep93xx_ac97_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_ac97_cold_reset(struct snd_ac97 *ac97)
{
	struct ep93xx_ac97_info *info = ep93xx_ac97_info;

	mutex_lock(&info->lock);

	/*
	 * For doing cold reset, we disable the AC97 controller interface, clear
	 * WINT and CODECREADY bits, and finally enable the interface again.
	 */
	ep93xx_ac97_write_reg(info, AC97GCR, 0);
	ep93xx_ac97_write_reg(info, AC97EOI, AC97EOI_CODECREADY | AC97EOI_WINT);
	ep93xx_ac97_write_reg(info, AC97GCR, AC97GCR_AC97IFE);

	/*
	 * Now, assert the reset and wait for the codec to become ready.
	 */
	ep93xx_ac97_write_reg(info, AC97RESET, AC97RESET_TIMEDRESET);
	ep93xx_ac97_write_reg(info, AC97IM, AC97_CODECREADY);
	if (!wait_for_completion_timeout(&info->done, AC97_TIMEOUT))
		dev_warn(info->dev, "codec cold reset timeout\n");

	/*
	 * Give the codec some time to come fully out from the reset. This way
	 * we ensure that the subsequent reads/writes will work.
	 */
	usleep_range(15000, 20000);

	mutex_unlock(&info->lock);
}