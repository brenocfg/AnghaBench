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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static int cs_len_prefix_opcode(uint8_t *item) {
	int i, len = 0;
	for (i = 0; i < 4; i++) {
		len += (item[i] != 0) ? 1 : 0;
	}
	return len;
}