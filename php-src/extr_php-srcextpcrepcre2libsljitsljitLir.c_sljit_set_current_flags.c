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
struct sljit_compiler {int dummy; } ;
typedef  struct sljit_compiler* sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  SLJIT_UNUSED_ARG (struct sljit_compiler*) ; 

void sljit_set_current_flags(struct sljit_compiler *compiler, sljit_s32 current_flags)
{
	SLJIT_UNUSED_ARG(compiler);
	SLJIT_UNUSED_ARG(current_flags);

#if (defined SLJIT_ARGUMENT_CHECKS && SLJIT_ARGUMENT_CHECKS)
	if ((current_flags & ~(VARIABLE_FLAG_MASK | SLJIT_I32_OP | SLJIT_SET_Z)) == 0) {
		compiler->last_flags = GET_FLAG_TYPE(current_flags) | (current_flags & (SLJIT_I32_OP | SLJIT_SET_Z));
	}
#endif
}