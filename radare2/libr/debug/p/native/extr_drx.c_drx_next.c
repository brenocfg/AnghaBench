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
typedef  int /*<<< orphan*/  drxt ;

/* Variables and functions */

int drx_next(drxt *drx) {
	int i;
	for (i = 0; i < 4; i++) {
		if (!drx[i]) {
			return i;
		}
	}
	return -1;
}