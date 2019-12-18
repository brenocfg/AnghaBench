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
struct TYPE_3__ {int /*<<< orphan*/  code_align; } ;
typedef  int /*<<< orphan*/  RAsmOp ;
typedef  TYPE_1__ RAsmCode ;

/* Variables and functions */
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int r_asm_pseudo_align(RAsmCode *acode, RAsmOp *op, char *input) {
	acode->code_align = r_num_math (NULL, input);
	return 0;
}