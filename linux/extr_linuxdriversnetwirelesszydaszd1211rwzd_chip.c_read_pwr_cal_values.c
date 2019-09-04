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
struct zd_chip {int /*<<< orphan*/  pwr_cal_values; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_CHANNEL_COUNT ; 
 int /*<<< orphan*/  E2P_PWR_CAL_VALUE1 ; 
 int read_values (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_pwr_cal_values(struct zd_chip *chip)
{
	return read_values(chip, chip->pwr_cal_values,
		        E2P_CHANNEL_COUNT, E2P_PWR_CAL_VALUE1,
			0);
}