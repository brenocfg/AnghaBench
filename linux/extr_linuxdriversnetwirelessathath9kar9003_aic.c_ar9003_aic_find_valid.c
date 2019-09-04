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
typedef  int u8 ;
typedef  size_t int16_t ;

/* Variables and functions */
 size_t ATH_AIC_MAX_BT_CHANNEL ; 

__attribute__((used)) static int16_t ar9003_aic_find_valid(bool *cal_sram_valid,
				     bool dir, u8 index)
{
	int16_t i;

	if (dir) {
		for (i = index + 1; i < ATH_AIC_MAX_BT_CHANNEL; i++) {
			if (cal_sram_valid[i])
				break;
		}
	} else {
		for (i = index - 1; i >= 0; i--) {
			if (cal_sram_valid[i])
				break;
		}
	}

	if ((i >= ATH_AIC_MAX_BT_CHANNEL) || (i < 0))
		i = -1;

	return i;
}