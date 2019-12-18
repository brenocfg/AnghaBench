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
 int /*<<< orphan*/  r_asm_set_pc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline int r_asm_pseudo_org(RAsm *a, char *input) {
	r_asm_set_pc (a, r_num_math (NULL, input));
	return 0;
}