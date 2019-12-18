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
struct cr16_cmd {int dummy; } ;

/* Variables and functions */
 int cr16_get_dstreg (int) ; 
 int cr16_get_opcode_159_0 (int) ; 
 int cr16_get_srcreg (int) ; 
 scalar_t__ cr16_print_ld_sw_opcode (struct cr16_cmd*,int) ; 
 int /*<<< orphan*/  cr16_print_long_reg (struct cr16_cmd*,int,int,int) ; 
 int /*<<< orphan*/  cr16_print_longregreg_reg (struct cr16_cmd*,int,int,int,int) ; 
 int /*<<< orphan*/  cr16_print_reg_reg_rel (struct cr16_cmd*,int,int,int,int) ; 
 int /*<<< orphan*/  cr16_print_reg_rel_reg (struct cr16_cmd*,int,int,int,int) ; 
 int /*<<< orphan*/  cr16_print_short_abs18 (struct cr16_cmd*,int,int) ; 
 int /*<<< orphan*/  cr16_print_short_reg_rel (struct cr16_cmd*,int,int,int) ; 
 int r_read_at_le16 (int /*<<< orphan*/  const*,int) ; 
 int r_read_le16 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int cr16_decode_ld_st(const ut8 *instr, struct cr16_cmd *cmd) {
	int ret = 2;
	ut32 disp32;
	ut16 disp16;

	ut16 c = r_read_le16 (instr);

	if (cr16_print_ld_sw_opcode(cmd, c)) {
		return -1;
	}

	switch (cr16_get_opcode_159_0(c) & (~0x20)) {
	case 0x04:
		ret = 4;
		if ((c & 0xC0) != 0xC0) {
			ret = -1;
			break;
		}
		disp16 = r_read_at_le16 (instr, 2);

		disp32 = disp16 | ((c & 0x0100) << 9) | ((c & 0x0020) << 11);

		cr16_print_short_abs18(cmd, cr16_get_srcreg(c), disp32);
		break;
	case 0x05:
		ret = 4;
		disp16 = r_read_at_le16 (instr, 2);

		if (cr16_print_short_reg_rel(cmd, cr16_get_srcreg(c),
				disp16, cr16_get_dstreg(c) & 0x9)) {
			return -1;
		}
		break;
	case 0x45:
		if (!(c & 0x1) || ((c >> 6) & 0x3) != 0x3) {
			ret = -1;
			break;
		}
		if (cr16_print_short_reg_rel(cmd, cr16_get_srcreg(c), 0,
					cr16_get_dstreg(c) & 0x9)) {
				return -1;
		}
		break;
	default:
		ret = -1;
	}

	if (ret != -1) {
		return ret;
	}

	switch ((c >> 11) & (~0x4)) {
	case 0x12:
		ret = 4;
		if (!(c & 1)) {
			ret = -1;
			break;
		}
		disp16 = r_read_at_le16 (instr, 2);
		disp32 = disp16 | (((c >> 9) & 0x3) << 16);

		cr16_print_reg_rel_reg(cmd, disp32, cr16_get_srcreg(c),
				cr16_get_dstreg(c), 0);
		break;

	case 0x13:
		ret = 4;
		disp16 = r_read_at_le16 (instr, 2);
		disp32 = disp16 | (((c >> 9) & 0x3) << 16);

		if (cr16_get_srcreg(c) == 0xF) {
			cr16_print_long_reg(cmd, disp32, cr16_get_dstreg(c), 0);
		} else {
			cr16_print_longregreg_reg(cmd, disp32, cr16_get_srcreg(c),
					cr16_get_dstreg(c), 0);
		}
		break;
	case 0x1B:
		ret = 4;
		disp16 = r_read_at_le16 (instr, 2);
		disp32 = disp16 | (((c >> 9) & 0x3) << 16);

		if (cr16_get_srcreg(c) == 0xF) {
			cr16_print_long_reg(cmd, disp32, cr16_get_dstreg(c), 1);
		} else {
			cr16_print_longregreg_reg(cmd, disp32, cr16_get_dstreg(c),
					cr16_get_srcreg(c), 1);
		}
		break;
	case 0x1A:
		ret = 4;
		disp16 = r_read_at_le16 (instr, 2);
		disp32 = disp16 | (((c >> 9) & 0x3) << 16);

		cr16_print_reg_rel_reg(cmd, disp32, cr16_get_srcreg(c),
				cr16_get_dstreg(c), 1);

		break;
	default:
		ret = -1;
	}

	if (ret != -1) {
		return ret;
	}

	switch (c >> 14) {
	case 0x3:
		ret = 2;
		disp16 = (c & 0x1) | ((c >> 8) & 0x1E);
		cr16_print_reg_reg_rel (cmd, cr16_get_srcreg (c),
				disp16, cr16_get_dstreg (c), 1);
		break;
	case 0x2:
		ret = 2;
		disp16 = (c & 0x1) | ((c >> 8) & 0x1E);
		cr16_print_reg_reg_rel  (cmd, cr16_get_srcreg (c),
				disp16, cr16_get_dstreg (c), 0);
		break;
	default:
		ret = -1;
	}
	return ret;
}