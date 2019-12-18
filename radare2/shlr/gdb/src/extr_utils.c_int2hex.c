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

int int2hex(int i) {
	if (i >= 0 && i <= 9) {
		return i + 48;
	}
	if (i >= 10 && i <= 15) {
		return i + 87;
	}
	return -1;
}