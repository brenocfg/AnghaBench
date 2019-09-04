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
 int /*<<< orphan*/  AC97IM ; 
 int /*<<< orphan*/  AC97SYNC ; 
 int /*<<< orphan*/  AC97SYNC_TIMEDSYNC ; 
 int /*<<< orphan*/  AC97_CODECREADY ; 
 int /*<<< orphan*/  AC97_TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct ep93xx_ac97_info* ep93xx_ac97_info ; 
 int /*<<< orphan*/  ep93xx_ac97_write_reg (struct ep93xx_ac97_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_ac97_warm_reset(struct snd_ac97 *ac97)
{
	struct ep93xx_ac97_info *info = ep93xx_ac97_info;

	mutex_lock(&info->lock);

	/*
	 * We are assuming that before this functions gets called, the codec
	 * BIT_CLK is stopped by forcing the codec into powerdown mode. We can
	 * control the SYNC signal directly via AC97SYNC register. Using
	 * TIMEDSYNC the controller will keep the SYNC high > 1us.
	 */
	ep93xx_ac97_write_reg(info, AC97SYNC, AC97SYNC_TIMEDSYNC);
	ep93xx_ac97_write_reg(info, AC97IM, AC97_CODECREADY);
	if (!wait_for_completion_timeout(&info->done, AC97_TIMEOUT))
		dev_warn(info->dev, "codec warm reset timeout\n");

	mutex_unlock(&info->lock);
}