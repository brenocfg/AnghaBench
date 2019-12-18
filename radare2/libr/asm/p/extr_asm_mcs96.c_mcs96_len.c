#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  size_t ut32 ;
struct TYPE_2__ {int type; int /*<<< orphan*/  ins; } ;
typedef  int /*<<< orphan*/  RStrBuf ;

/* Variables and functions */
 int MCS96_2B ; 
 int MCS96_2OP ; 
 int MCS96_3B ; 
 int MCS96_3B_OR_4B ; 
 int MCS96_4B ; 
 int MCS96_4B_OR_5B ; 
 int MCS96_5B ; 
 int MCS96_5B_OR_6B ; 
 int MCS96_FE ; 
 int MCS96_REG_8 ; 
 int /*<<< orphan*/ * mcs96_fe_op ; 
 TYPE_1__* mcs96_op ; 
 int /*<<< orphan*/  r_strbuf_appendf (int /*<<< orphan*/ *,char*,int const,int const) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcs96_len (const ut8 *buf, int len, RStrBuf *asm_buf) {
	int ret = 1;
	if (buf[0] == 0xfe) {
		if (len < 2) {
			return 0;
		}
		if (mcs96_op[buf[1]].type & MCS96_FE) {
			if (mcs96_op[buf[1]].type & MCS96_5B_OR_6B) {
				if (len < 3) {
					return 0;
				}
				ret = 6 + (buf[2] & 0x1);
			}
			if (mcs96_op[buf[1]].type & MCS96_4B_OR_5B) {
				if (len < 3) {
					return 0;
				}
				ret = 5 + (buf[2] & 0x1);
			}
			if (mcs96_op[buf[1]].type & MCS96_3B_OR_4B) {
				if (len < 3) {
					return 0;
				}
				ret = 4 + (buf[1] & 0x1);
			}
			if (mcs96_op[buf[1]].type & MCS96_5B) {
				ret = 6;
			}
			if (mcs96_op[buf[1]].type & MCS96_4B) {
				ret = 5;
			}
			if (mcs96_op[buf[1]].type & MCS96_3B) {
				ret = 4;
			}
			if (mcs96_op[buf[1]].type & MCS96_2B) {
				ret = 3;
			}
			if (ret <= len) {
				const ut32 fe_idx = ((buf[1] & 0x70) >> 4) ^ 0x4;
				r_strbuf_set (asm_buf, mcs96_fe_op[fe_idx]);
				if ((mcs96_op[buf[1]].type & (MCS96_2OP | MCS96_REG_8)) == (MCS96_2OP | MCS96_REG_8) &&
					buf[2] > 0x19 && buf[3] > 0x19) {
					r_strbuf_appendf(asm_buf, " rb%02x, rb%02x", buf[2] - 0x1a, buf[3] - 0x1a);
				}
			} else {
				ret = 0;
			}
			return ret;
		}
	}
	if (mcs96_op[buf[0]].type & MCS96_5B_OR_6B) {
		if (len < 2) {
			return 0;
		}
		ret = 5 + (buf[1] & 0x1);
	}
	if (mcs96_op[buf[0]].type & MCS96_4B_OR_5B) {
		if (len < 2) {
			return 0;
		}
		ret = 4 + (buf[1] & 0x1);
	}
	if (mcs96_op[buf[0]].type & MCS96_3B_OR_4B) {
		if (len < 2) {
			return 0;
		}
		ret = 3 + (buf[1] & 0x1);
	}
	if (mcs96_op[buf[0]].type & MCS96_5B) {
		ret = 5;
	}
	if (mcs96_op[buf[0]].type & MCS96_4B) {
		ret = 4;
	}
	if (mcs96_op[buf[0]].type & MCS96_3B) {
		ret = 3;
	}
	if (mcs96_op[buf[0]].type & MCS96_2B) {
		ret = 2;
	}
	if (ret <= len) {
		r_strbuf_set (asm_buf, mcs96_op[buf[0]].ins);
		if ((mcs96_op[buf[0]].type & (MCS96_2OP | MCS96_REG_8)) == (MCS96_2OP | MCS96_REG_8) &&
			buf[1] > 0x19 && buf[2] > 0x19) {
			r_strbuf_appendf(asm_buf, " rb%02x, rb%02x", buf[1] - 0x1a, buf[2] - 0x1a);
		}
	} else {
		ret = 0;
	}
	return ret;
}