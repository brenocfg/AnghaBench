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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  drxt ;

/* Variables and functions */
 scalar_t__ drx_get (int /*<<< orphan*/ *,int,int*,int*,int*,int*) ; 

int drx_get_at(drxt *drx, ut64 at_addr) {
	ut64 addr;
	int i, rwx, len, g, en;

	for (i = 0; i < 8; i++) {
		if (i == 4 || i == 5) {
			continue;
		}
		rwx = len = g = en = 0;
		addr = drx_get (drx, i, &rwx, &len, &g, &en);
		if (addr == at_addr) {
			return i;
		}
	}
	return -1;
}