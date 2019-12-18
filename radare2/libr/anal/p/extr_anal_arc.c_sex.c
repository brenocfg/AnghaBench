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

__attribute__((used)) static int sex(int bits, int imm) {
	int maxsint = (1 << (bits - 1)) - 1;
	int maxuint = (1 << (bits)) - 1;

	if (imm > maxsint) {
		/* sign extend */
		imm = -maxuint + imm - 1;
	}
	return imm;
}