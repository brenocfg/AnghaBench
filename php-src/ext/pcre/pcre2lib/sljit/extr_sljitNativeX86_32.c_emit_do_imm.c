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
typedef  int /*<<< orphan*/  sljit_u8 ;
typedef  int /*<<< orphan*/  sljit_sw ;
typedef  int /*<<< orphan*/  sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  INC_SIZE (int) ; 
 int /*<<< orphan*/  SLJIT_SUCCESS ; 
 scalar_t__ ensure_buf (struct sljit_compiler*,int) ; 
 int /*<<< orphan*/  sljit_unaligned_store_sw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sljit_s32 emit_do_imm(struct sljit_compiler *compiler, sljit_u8 opcode, sljit_sw imm)
{
	sljit_u8 *inst;

	inst = (sljit_u8*)ensure_buf(compiler, 1 + 1 + sizeof(sljit_sw));
	FAIL_IF(!inst);
	INC_SIZE(1 + sizeof(sljit_sw));
	*inst++ = opcode;
	sljit_unaligned_store_sw(inst, imm);
	return SLJIT_SUCCESS;
}