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

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_TS_TSENSSTAT_DATA_BITS ; 
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_thermal_temp2adc(int temp, int offset, int slope)
{
	temp -= offset;
	temp /= slope;

	if (temp < 0)
		temp = 0;
	if (temp >= BIT(BCM2835_TS_TSENSSTAT_DATA_BITS))
		temp = BIT(BCM2835_TS_TSENSSTAT_DATA_BITS) - 1;

	return temp;
}