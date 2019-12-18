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
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_asm_set_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline int r_asm_pseudo_bits(RAsm *a, char *input) {
	if (!(r_asm_set_bits (a, r_num_math (NULL, input)))) {
		eprintf ("Error: Unsupported value for .bits.\n");
		return -1;
	}
	return 0;
}