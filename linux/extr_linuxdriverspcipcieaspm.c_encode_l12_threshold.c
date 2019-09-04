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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void encode_l12_threshold(u32 threshold_us, u32 *scale, u32 *value)
{
	u32 threshold_ns = threshold_us * 1000;

	/* See PCIe r3.1, sec 7.33.3 and sec 6.18 */
	if (threshold_ns < 32) {
		*scale = 0;
		*value = threshold_ns;
	} else if (threshold_ns < 1024) {
		*scale = 1;
		*value = threshold_ns >> 5;
	} else if (threshold_ns < 32768) {
		*scale = 2;
		*value = threshold_ns >> 10;
	} else if (threshold_ns < 1048576) {
		*scale = 3;
		*value = threshold_ns >> 15;
	} else if (threshold_ns < 33554432) {
		*scale = 4;
		*value = threshold_ns >> 20;
	} else {
		*scale = 5;
		*value = threshold_ns >> 25;
	}
}