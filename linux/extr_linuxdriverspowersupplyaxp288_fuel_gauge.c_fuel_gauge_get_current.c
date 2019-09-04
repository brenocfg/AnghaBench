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
struct axp288_fg_info {int /*<<< orphan*/ * iio_channel; } ;

/* Variables and functions */
 size_t BAT_CHRG_CURR ; 
 size_t BAT_D_CURR ; 
 int iio_read_channel_raw (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fuel_gauge_get_current(struct axp288_fg_info *info, int *cur)
{
	int ret, discharge;

	/* First check discharge current, so that we do only 1 read on bat. */
	ret = iio_read_channel_raw(info->iio_channel[BAT_D_CURR], &discharge);
	if (ret < 0)
		return ret;

	if (discharge > 0) {
		*cur = -1 * discharge;
		return 0;
	}

	return iio_read_channel_raw(info->iio_channel[BAT_CHRG_CURR], cur);
}