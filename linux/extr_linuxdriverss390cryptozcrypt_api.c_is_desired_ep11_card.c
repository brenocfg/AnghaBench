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
struct ep11_target_dev {unsigned int ap_id; } ;

/* Variables and functions */

__attribute__((used)) static bool is_desired_ep11_card(unsigned int dev_id,
				 unsigned short target_num,
				 struct ep11_target_dev *targets)
{
	while (target_num-- > 0) {
		if (dev_id == targets->ap_id)
			return true;
		targets++;
	}
	return false;
}