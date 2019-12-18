#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ RAsmState ;

/* Variables and functions */
 int /*<<< orphan*/  R_SYS_ARCH ; 
 int R_SYS_BITS ; 
 int R_SYS_BITS_64 ; 
 int /*<<< orphan*/  r_anal_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_anal_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_asm_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_asm_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __as_set_archbits(RAsmState *as) {
	r_asm_use (as->a, R_SYS_ARCH);
	r_anal_use (as->anal, R_SYS_ARCH);

	int sysbits = (R_SYS_BITS & R_SYS_BITS_64)? 64: 32;
	r_asm_set_bits (as->a, sysbits);
	r_anal_set_bits (as->anal, sysbits);
}