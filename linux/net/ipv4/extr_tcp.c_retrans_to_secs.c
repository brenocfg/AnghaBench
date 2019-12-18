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

__attribute__((used)) static int retrans_to_secs(u8 retrans, int timeout, int rto_max)
{
	int period = 0;

	if (retrans > 0) {
		period = timeout;
		while (--retrans) {
			timeout <<= 1;
			if (timeout > rto_max)
				timeout = rto_max;
			period += timeout;
		}
	}
	return period;
}