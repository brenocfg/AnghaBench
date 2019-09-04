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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 phydm_get_current_igi(u8 dig_max_of_min, u8 rssi_min,
				       u8 current_igi)
{
	if (rssi_min < dig_max_of_min) {
		if (current_igi < rssi_min)
			return rssi_min;
	} else {
		if (current_igi < dig_max_of_min)
			return dig_max_of_min;
	}
	return current_igi;
}