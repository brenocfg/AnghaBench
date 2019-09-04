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
typedef  int /*<<< orphan*/  RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int r_asm_pseudo_intN (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static inline int r_asm_pseudo_int16(RAsm *a, RAsmOp *op, char *input) {
	return r_asm_pseudo_intN (a, op, input, 2);
}