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

__attribute__((used)) static ut8 gprobe_checksum (const ut8 *p, unsigned int size) {
	ut8 res = 0;
	unsigned int k;

	for (k = 0; k < size; ++k) {
		res += p[k];
	}

	res = ~res + 1;

	return res;
}