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
struct sljit_compiler {int scratches; int saveds; scalar_t__ logical_local_size; } ;
typedef  scalar_t__ sljit_sw ;
typedef  int sljit_s32 ;

/* Variables and functions */
 scalar_t__ FUNCTION_CHECK_IS_FREG (int) ; 
 int SLJIT_MEM1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLJIT_SP ; 
 int function_check_src_mem (struct sljit_compiler*,int,scalar_t__) ; 

__attribute__((used)) static sljit_s32 function_fcheck(struct sljit_compiler *compiler, sljit_s32 p, sljit_sw i)
{
	if (compiler->scratches == -1 || compiler->saveds == -1)
		return 0;

	if (FUNCTION_CHECK_IS_FREG(p))
		return (i == 0);

	if (p == SLJIT_MEM1(SLJIT_SP))
		return (i >= 0 && i < compiler->logical_local_size);

	return function_check_src_mem(compiler, p, i);
}