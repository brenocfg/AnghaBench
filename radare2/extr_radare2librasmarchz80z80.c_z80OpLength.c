#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; scalar_t__ op_moar; } ;
typedef  TYPE_1__ z80_opcode ;
typedef  size_t ut8 ;

/* Variables and functions */
 int Z80_ARG16 ; 
 int Z80_ARG8 ; 
 int Z80_ENC0 ; 
 int Z80_ENC1 ; 
 int Z80_OP16 ; 
 int Z80_OP24 ; 
 int Z80_OP8 ; 
 int Z80_OP_UNK ; 
 size_t z80_ed_branch_index_res (size_t const) ; 
 size_t z80_fddd_branch_index_res (size_t const) ; 
 TYPE_1__* z80_op ; 

__attribute__((used)) static int z80OpLength (const ut8 *buf, int len) {
	z80_opcode *op;
	int type = 0, ret = 0;
	if (len < 1) {
		return 0;
	}
	op = z80_op;
	if (op[buf[0]].type & Z80_OP_UNK) {
		if (len < 2) {
			return 0;
		}
		if (op[buf[0]].type & Z80_ENC0) {
			op = (z80_opcode *)op[buf[0]].op_moar;
			type = op[z80_fddd_branch_index_res(buf[1])].type;
		} else if (op[buf[0]].type & Z80_ENC1) {
			op = (z80_opcode *)op[buf[0]].op_moar;
			type = op[z80_ed_branch_index_res(buf[1])].type;
		}
	} else {
		type = op[buf[0]].type;
	}
	if (type & Z80_OP8) {
		ret++;
	}
	if ((type & Z80_ARG8) && !(type & Z80_ARG16)) { //XXX
		ret++;
	}
	if (type & Z80_OP16) {
		ret += 2;
	}
	if (type & Z80_ARG16) {
		ret += 2;
	}
	if (type & Z80_OP24) {
		ret += 3;
	}
	if (ret > len) {
		return 0;
	}
	return ret;
}