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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  const_gimple ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_STRING_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimple_asm_clobber_op (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int gimple_asm_nclobbers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline bool gimple_asm_clobbers_memory_p(const_gimple stmt)
{
	unsigned i;

	for (i = 0; i < gimple_asm_nclobbers(stmt); i++) {
		tree op = gimple_asm_clobber_op(stmt, i);

		if (!strcmp(TREE_STRING_POINTER(TREE_VALUE(op)), "memory"))
			return true;
	}

	return false;
}