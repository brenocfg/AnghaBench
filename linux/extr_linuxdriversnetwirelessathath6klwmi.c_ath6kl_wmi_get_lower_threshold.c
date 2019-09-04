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
typedef  size_t u32 ;
struct sq_threshold_params {scalar_t__* lower_threshold; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */

__attribute__((used)) static u8 ath6kl_wmi_get_lower_threshold(s16 rssi,
					 struct sq_threshold_params *sq_thresh,
					 u32 size)
{
	u32 index;
	u8 threshold = (u8) sq_thresh->lower_threshold[size - 1];

	/* The list is already in sorted order. Get the next lower value */
	for (index = 0; index < size; index++) {
		if (rssi > sq_thresh->lower_threshold[index]) {
			threshold = (u8) sq_thresh->lower_threshold[index];
			break;
		}
	}

	return threshold;
}