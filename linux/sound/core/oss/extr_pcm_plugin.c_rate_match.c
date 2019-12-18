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

__attribute__((used)) static int rate_match(unsigned int src_rate, unsigned int dst_rate)
{
	unsigned int low = (src_rate * 95) / 100;
	unsigned int high = (src_rate * 105) / 100;
	return dst_rate >= low && dst_rate <= high;
}