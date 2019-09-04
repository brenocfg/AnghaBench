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
typedef  int ut8 ;

/* Variables and functions */

__attribute__((used)) static bool checkSparse(const ut8 *p, int len, int ch) {
	int i;
	ut8 q = *p;
	if (ch && ch != q) {
		return false;
	}
	for (i = 1; i < len; i++) {
		if (p[i] != q) {
			return false;
		}
	}
	return true;
}