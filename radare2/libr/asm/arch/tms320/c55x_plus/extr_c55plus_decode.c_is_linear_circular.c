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
typedef  int ut32 ;

/* Variables and functions */

__attribute__((used)) static bool is_linear_circular(ut32 ins_bits) {
	ut8 op, op2, op3;
	op = (ins_bits >> 6) | 16 * (ins_bits & 3);
	op2 = (ins_bits >> 2) & 0xF;
	op3 = op2 & 0xF;
	return (op == 26 || op == 30 || (op3 > 7 && op3 != 15));
}