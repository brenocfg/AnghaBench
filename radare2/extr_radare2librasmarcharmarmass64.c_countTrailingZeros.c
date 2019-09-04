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
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static int countTrailingZeros(ut32 x) {
	int count = 0;
	while (x > 0) {
		if ((x & 1) == 1) {
			break;
		} else {
			count ++;
			x = x >> 1;
		}
	}
	return count;
}