#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_8__ {int type; } ;
struct TYPE_7__ {int type; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
 int Z80_ARG16 ; 
 int Z80_ARG8 ; 
 int Z80_OP16 ; 
 int Z80_OP24 ; 
 int Z80_OP8 ; 
 TYPE_4__* dd ; 
 TYPE_3__* ed ; 
 TYPE_2__* fd ; 
 int z80_ed_branch_index_res (int const) ; 
 size_t z80_fddd_branch_index_res (int const) ; 
 TYPE_1__* z80_op ; 

__attribute__((used)) static void z80_op_size(const ut8 *data, int len, int *size, int *size_prefix) {
	int type = 0;
	if (len <1) {
		return;
	}
	switch (data[0]) {
	case 0xed:
		if (len > 1) {
			int idx = z80_ed_branch_index_res (data[1]);
			type = ed[idx].type;
		}
		break;
	case 0xcb:
		type = Z80_OP16;
		break;
	case 0xdd:
		if (len >1) {
			type = dd[z80_fddd_branch_index_res(data[1])].type;
		}
		break;
	case 0xfd:
		if (len > 1) {
			type = fd[z80_fddd_branch_index_res(data[1])].type;
		}
		break;
	default:
		type = z80_op[data[0]].type;
		break;
	}

	if (type & Z80_OP8) {
		*size_prefix = 1;
	} else if (type & Z80_OP16) {
		*size_prefix = 2;
	} else if (type & Z80_OP24) {
		*size_prefix = 3;
	}

	if (type & Z80_ARG16) {
		*size = *size_prefix + 2;
	} else if (type & Z80_ARG8) {
		*size = *size_prefix + 1;
	} else {
		*size = *size_prefix;
	}
}