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
typedef  scalar_t__ sljit_s32 ;

/* Variables and functions */
 int EX86_PREF_66 ; 
 int EX86_SSE2 ; 
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  GROUP_0F ; 
 scalar_t__ SLJIT_SUCCESS ; 
 int /*<<< orphan*/ * emit_x86_instruction (struct sljit_compiler*,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sljit_s32 emit_sse2_logic(struct sljit_compiler *compiler, sljit_u8 opcode,
	sljit_s32 pref66, sljit_s32 xmm1, sljit_s32 xmm2, sljit_sw xmm2w)
{
	sljit_u8 *inst;

	inst = emit_x86_instruction(compiler, 2 | (pref66 ? EX86_PREF_66 : 0) | EX86_SSE2, xmm1, 0, xmm2, xmm2w);
	FAIL_IF(!inst);
	*inst++ = GROUP_0F;
	*inst = opcode;
	return SLJIT_SUCCESS;
}