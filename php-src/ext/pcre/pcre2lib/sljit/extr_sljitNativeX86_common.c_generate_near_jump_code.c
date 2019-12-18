#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int target; TYPE_1__* label; } ;
struct sljit_jump {int flags; int addr; TYPE_2__ u; } ;
typedef  int sljit_uw ;
typedef  int /*<<< orphan*/  sljit_u8 ;
typedef  int sljit_sw ;
typedef  int /*<<< orphan*/  sljit_s8 ;
typedef  scalar_t__ sljit_s32 ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_i32 ; 
 scalar_t__ GROUP_0F ; 
 int HALFWORD_MAX ; 
 int HALFWORD_MIN ; 
 int /*<<< orphan*/  JMP_i32 ; 
 int /*<<< orphan*/  JMP_i8 ; 
 int JUMP_LABEL ; 
 int PATCH_MB ; 
 int PATCH_MW ; 
 scalar_t__ SLJIT_FAST_CALL ; 
 scalar_t__ SLJIT_JUMP ; 
 int /*<<< orphan*/ * generate_far_jump_code (struct sljit_jump*,int /*<<< orphan*/ *,scalar_t__) ; 
 void* get_jump_code (scalar_t__) ; 

__attribute__((used)) static sljit_u8* generate_near_jump_code(struct sljit_jump *jump, sljit_u8 *code_ptr, sljit_u8 *code, sljit_s32 type, sljit_sw executable_offset)
{
	sljit_s32 short_jump;
	sljit_uw label_addr;

	if (jump->flags & JUMP_LABEL)
		label_addr = (sljit_uw)(code + jump->u.label->size);
	else
		label_addr = jump->u.target - executable_offset;

	short_jump = (sljit_sw)(label_addr - (jump->addr + 2)) >= -128 && (sljit_sw)(label_addr - (jump->addr + 2)) <= 127;

#if (defined SLJIT_CONFIG_X86_64 && SLJIT_CONFIG_X86_64)
	if ((sljit_sw)(label_addr - (jump->addr + 1)) > HALFWORD_MAX || (sljit_sw)(label_addr - (jump->addr + 1)) < HALFWORD_MIN)
		return generate_far_jump_code(jump, code_ptr, type);
#endif

	if (type == SLJIT_JUMP) {
		if (short_jump)
			*code_ptr++ = JMP_i8;
		else
			*code_ptr++ = JMP_i32;
		jump->addr++;
	}
	else if (type >= SLJIT_FAST_CALL) {
		short_jump = 0;
		*code_ptr++ = CALL_i32;
		jump->addr++;
	}
	else if (short_jump) {
		*code_ptr++ = get_jump_code(type) - 0x10;
		jump->addr++;
	}
	else {
		*code_ptr++ = GROUP_0F;
		*code_ptr++ = get_jump_code(type);
		jump->addr += 2;
	}

	if (short_jump) {
		jump->flags |= PATCH_MB;
		code_ptr += sizeof(sljit_s8);
	} else {
		jump->flags |= PATCH_MW;
		code_ptr += sizeof(sljit_s32);
	}

	return code_ptr;
}