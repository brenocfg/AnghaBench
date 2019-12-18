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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int ut16 ;
struct TYPE_3__ {int jump; void* type; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
#define  H8300_JMP_1 130 
#define  H8300_JMP_2 129 
#define  H8300_JMP_3 128 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_UJMP ; 
 int /*<<< orphan*/  r_mem_swapendian (int*,int const*,int) ; 

__attribute__((used)) static void h8300_anal_jmp(RAnalOp *op, ut64 addr, const ut8 *buf) {
	ut16 ad;

	switch (buf[0]) {
	case H8300_JMP_1:
		op->type = R_ANAL_OP_TYPE_UJMP;
		break;
	case H8300_JMP_2:
		op->type = R_ANAL_OP_TYPE_JMP;
		r_mem_swapendian ((ut8*)&ad, buf + 2, sizeof (ut16));
		op->jump = ad;
		break;
	case H8300_JMP_3:
		op->type = R_ANAL_OP_TYPE_UJMP;
		op->jump = buf[1];
		break;
	}
}