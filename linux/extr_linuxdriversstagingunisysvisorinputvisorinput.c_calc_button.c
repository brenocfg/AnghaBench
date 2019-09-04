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
 int BTN_LEFT ; 
 int BTN_MIDDLE ; 
 int BTN_RIGHT ; 
 int EINVAL ; 

__attribute__((used)) static int calc_button(int x)
{
	switch (x) {
	case 1:
		return BTN_LEFT;
	case 2:
		return BTN_MIDDLE;
	case 3:
		return BTN_RIGHT;
	default:
		return -EINVAL;
	}
}