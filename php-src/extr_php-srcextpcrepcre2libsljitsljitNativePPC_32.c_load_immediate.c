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
typedef  int sljit_sw ;
typedef  int /*<<< orphan*/  sljit_s32 ;

/* Variables and functions */
 int A (int /*<<< orphan*/ ) ; 
 int ADDI ; 
 int ADDIS ; 
 int D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int IMM (int) ; 
 int ORI ; 
 int S (int /*<<< orphan*/ ) ; 
 int SIMM_MAX ; 
 int SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 int /*<<< orphan*/  TMP_ZERO ; 
 int /*<<< orphan*/  push_inst (struct sljit_compiler*,int) ; 

__attribute__((used)) static sljit_s32 load_immediate(struct sljit_compiler *compiler, sljit_s32 reg, sljit_sw imm)
{
	if (imm <= SIMM_MAX && imm >= SIMM_MIN)
		return push_inst(compiler, ADDI | D(reg) | A(0) | IMM(imm));

	if (!(imm & ~0xffff))
		return push_inst(compiler, ORI | S(TMP_ZERO) | A(reg) | IMM(imm));

	FAIL_IF(push_inst(compiler, ADDIS | D(reg) | A(0) | IMM(imm >> 16)));
	return (imm & 0xffff) ? push_inst(compiler, ORI | S(reg) | A(reg) | IMM(imm)) : SLJIT_SUCCESS;
}