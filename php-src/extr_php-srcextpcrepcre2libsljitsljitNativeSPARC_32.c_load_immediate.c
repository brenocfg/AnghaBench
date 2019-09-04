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
 int D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int IMM (int) ; 
 int IMM_ARG ; 
 int OR ; 
 int S1 (int /*<<< orphan*/ ) ; 
 int SETHI ; 
 int SIMM_MAX ; 
 int SIMM_MIN ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 int /*<<< orphan*/  push_inst (struct sljit_compiler*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sljit_s32 load_immediate(struct sljit_compiler *compiler, sljit_s32 dst, sljit_sw imm)
{
	if (imm <= SIMM_MAX && imm >= SIMM_MIN)
		return push_inst(compiler, OR | D(dst) | S1(0) | IMM(imm), DR(dst));

	FAIL_IF(push_inst(compiler, SETHI | D(dst) | ((imm >> 10) & 0x3fffff), DR(dst)));
	return (imm & 0x3ff) ? push_inst(compiler, OR | D(dst) | S1(dst) | IMM_ARG | (imm & 0x3ff), DR(dst)) : SLJIT_SUCCESS;
}