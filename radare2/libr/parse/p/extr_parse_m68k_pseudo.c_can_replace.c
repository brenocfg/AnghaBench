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

__attribute__((used)) static bool can_replace(const char *str, int idx, int max_operands) {
	if (str[idx] > '9' || str[idx] < '1') {
		return false;
	}
	if (str[idx + 1] != '\x00' && str[idx + 1] <= '9' && str[idx + 1] >= '1') {
		return false;
	}
	if ((int)((int)str[idx] - 0x30) > max_operands) {
		return false;
	}
	return true;
}