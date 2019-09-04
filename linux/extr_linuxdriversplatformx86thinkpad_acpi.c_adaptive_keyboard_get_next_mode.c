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
 int ARRAY_SIZE (int*) ; 
 int* adaptive_keyboard_modes ; 

__attribute__((used)) static int adaptive_keyboard_get_next_mode(int mode)
{
	size_t i;
	size_t max_mode = ARRAY_SIZE(adaptive_keyboard_modes) - 1;

	for (i = 0; i <= max_mode; i++) {
		if (adaptive_keyboard_modes[i] == mode)
			break;
	}

	if (i >= max_mode)
		i = 0;
	else
		i++;

	return adaptive_keyboard_modes[i];
}