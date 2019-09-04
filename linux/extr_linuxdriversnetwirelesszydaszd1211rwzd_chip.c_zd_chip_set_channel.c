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
typedef  int /*<<< orphan*/  u8 ;
struct zd_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CONFIG_PHILIPS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int patch_6m_band_edge (struct zd_chip*,int /*<<< orphan*/ ) ; 
 int patch_cck_gain (struct zd_chip*) ; 
 int update_channel_integration_and_calibration (struct zd_chip*,int /*<<< orphan*/ ) ; 
 int zd_chip_lock_phy_regs (struct zd_chip*) ; 
 int zd_chip_unlock_phy_regs (struct zd_chip*) ; 
 int zd_iowrite32_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zd_rf_set_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int zd_chip_set_channel(struct zd_chip *chip, u8 channel)
{
	int r, t;

	mutex_lock(&chip->mutex);
	r = zd_chip_lock_phy_regs(chip);
	if (r)
		goto out;
	r = zd_rf_set_channel(&chip->rf, channel);
	if (r)
		goto unlock;
	r = update_channel_integration_and_calibration(chip, channel);
	if (r)
		goto unlock;
	r = patch_cck_gain(chip);
	if (r)
		goto unlock;
	r = patch_6m_band_edge(chip, channel);
	if (r)
		goto unlock;
	r = zd_iowrite32_locked(chip, 0, CR_CONFIG_PHILIPS);
unlock:
	t = zd_chip_unlock_phy_regs(chip);
	if (t && !r)
		r = t;
out:
	mutex_unlock(&chip->mutex);
	return r;
}