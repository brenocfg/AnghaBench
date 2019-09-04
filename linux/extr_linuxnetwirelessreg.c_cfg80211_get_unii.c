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
 int EINVAL ; 

int cfg80211_get_unii(int freq)
{
	/* UNII-1 */
	if (freq >= 5150 && freq <= 5250)
		return 0;

	/* UNII-2A */
	if (freq > 5250 && freq <= 5350)
		return 1;

	/* UNII-2B */
	if (freq > 5350 && freq <= 5470)
		return 2;

	/* UNII-2C */
	if (freq > 5470 && freq <= 5725)
		return 3;

	/* UNII-3 */
	if (freq > 5725 && freq <= 5825)
		return 4;

	return -EINVAL;
}