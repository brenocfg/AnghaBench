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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;
typedef  int ut16 ;
struct winedbg_arm_insn {long long jmp; long long fail; void* str_hex; void* str_asm; int /*<<< orphan*/  buf; int /*<<< orphan*/  thumb; } ;
struct inst_thumb16 {int mask; int pattern; int /*<<< orphan*/  (* func ) (struct winedbg_arm_insn*,int) ;} ;
struct inst_arm {int mask; int pattern; int /*<<< orphan*/  (* func ) (struct winedbg_arm_insn*,int) ;} ;

/* Variables and functions */
 int ARM_INSN_SIZE ; 
 int THUMB2_INSN_SIZE ; 
 int THUMB_INSN_SIZE ; 
 int db_get_inst (int /*<<< orphan*/ ,int) ; 
 void* r_str_appendf (void*,char*,int,...) ; 
 int /*<<< orphan*/  stub1 (struct winedbg_arm_insn*,int) ; 
 int /*<<< orphan*/  stub2 (struct winedbg_arm_insn*,int) ; 
 int /*<<< orphan*/  stub3 (struct winedbg_arm_insn*,int) ; 
 int /*<<< orphan*/  tbl_arm ; 
 int /*<<< orphan*/  tbl_thumb16 ; 
 int /*<<< orphan*/  tbl_thumb32 ; 

int arm_disasm_one_insn(struct winedbg_arm_insn *arminsn) {
	struct inst_arm *a_ptr = (struct inst_arm *)&tbl_arm;
	struct inst_thumb16 *t_ptr = (struct inst_thumb16 *)&tbl_thumb16;
	struct inst_arm *t2_ptr = (struct inst_arm *)&tbl_thumb32;
	ut32 inst;
	ut16 tinst;
	int size;
	int matched = 0;

	arminsn->jmp = arminsn->fail = -1LL;
	if (!arminsn->thumb) {
		size = ARM_INSN_SIZE;
		inst = db_get_inst(arminsn->buf, size);
		while (a_ptr->func) {
			if ((inst & a_ptr->mask) ==  a_ptr->pattern) {
				matched = 1;
				break;
			}
			a_ptr++;
		}

		if (!matched) {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "Unknown ARM Instruction: %08x", inst);
		}
		else {
			a_ptr->func(arminsn, inst);
		}
		arminsn->str_hex = r_str_appendf (arminsn->str_hex, "%02x%02x%02x%02x",
				*((ut8*)(&inst)), *((ut8*)(&inst)+1),  *((ut8*)(&inst)+2),  *((ut8*)(&inst)+3));
		return size;
	} else {
		tinst = db_get_inst(arminsn->buf, THUMB_INSN_SIZE);
		switch (tinst & 0xf800) {
		case 0xe800:
		case 0xf000:
		case 0xf800:
			size = THUMB2_INSN_SIZE;
			inst = db_get_inst(arminsn->buf+1, THUMB_INSN_SIZE);
			inst |= (tinst << 16);

			while (t2_ptr->func) {
				if ((inst & t2_ptr->mask) ==  t2_ptr->pattern) {
					matched = 1;
					break;
				}
				t2_ptr++;
			}

			if (!matched) {
				arminsn->str_asm = r_str_appendf (arminsn->str_asm, "Unknown Thumb2 Instruction: %08x", inst);
			}
			else {
				t2_ptr->func(arminsn, inst);
			} 
			arminsn->str_hex = r_str_appendf (arminsn->str_hex, "%02x%02x%02x%02x",
					*((ut8*)(&inst)), *((ut8*)(&inst)+1),  *((ut8*)(&inst)+2),  *((ut8*)(&inst)+3));
			return size;
		default:
			break;
		}

		size = THUMB_INSN_SIZE;
		while (t_ptr->func) {
			if ((tinst & t_ptr->mask) ==  t_ptr->pattern) {
				matched = 1;
				break;
			}
			t_ptr++;
		}

		if (!matched) {
			arminsn->str_asm = r_str_appendf (arminsn->str_asm, "Unknown Thumb Instruction: %04x", tinst);
		}
		else {
			t_ptr->func(arminsn, tinst);
		}
		arminsn->str_hex = r_str_appendf (arminsn->str_hex, "%02x%02x", *((ut8*)(&tinst)), *((ut8*)(&tinst)+1));
		return size;
	}
	return size;
}