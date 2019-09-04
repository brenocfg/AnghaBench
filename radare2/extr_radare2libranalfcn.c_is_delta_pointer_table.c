#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ st32 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_14__ {scalar_t__ jmpabove; } ;
struct TYPE_13__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* is_valid_offset ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {TYPE_2__ opt; TYPE_1__ iob; } ;
struct TYPE_16__ {scalar_t__ addr; } ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ addr; scalar_t__ ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ RAnalOp ;
typedef  TYPE_4__ RAnalFunction ;
typedef  TYPE_5__ RAnal ;

/* Variables and functions */
 int JMPTBL_LEA_SEARCH_SZ ; 
 scalar_t__ JMPTBL_MAXFCNSIZE ; 
 int R_ANAL_OP_MASK_BASIC ; 
 int R_ANAL_OP_MASK_HINT ; 
 scalar_t__ R_ANAL_OP_TYPE_ADD ; 
 scalar_t__ R_ANAL_OP_TYPE_MOV ; 
 scalar_t__ R_ANAL_OP_TYPE_RJMP ; 
 scalar_t__ R_ANAL_OP_TYPE_UJMP ; 
 int r_anal_op (TYPE_5__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  r_anal_op_fini (TYPE_3__*) ; 
 scalar_t__ r_read_le32 (scalar_t__*) ; 
 int /*<<< orphan*/  read_ahead (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_delta_pointer_table(RAnal *anal, RAnalFunction *fcn, ut64 addr, ut64 lea_ptr, ut64 *jmptbl_addr, RAnalOp *jmp_aop) {
	int i;
	ut64 dst;
	st32 jmptbl[64] = {0};
	/* check if current instruction is followed by an ujmp */
	ut8 buf[JMPTBL_LEA_SEARCH_SZ];
	RAnalOp *aop = jmp_aop;
	RAnalOp mov_aop = {0};
	RAnalOp add_aop = {0};

	read_ahead (anal, addr, (ut8*)buf, sizeof (buf));
	bool isValid = false;
	for (i = 0; i + 8 < JMPTBL_LEA_SEARCH_SZ; i++) {
		ut64 at = addr + i;
		int left = JMPTBL_LEA_SEARCH_SZ - i;
		int len = r_anal_op (anal, aop, at, buf + i, left, R_ANAL_OP_MASK_BASIC | R_ANAL_OP_MASK_HINT);
		if (len < 1) {
			len = 1;
		}
		if (aop->type == R_ANAL_OP_TYPE_UJMP || aop->type == R_ANAL_OP_TYPE_RJMP) {
			isValid = true;
			break;
		}
		if (aop->type == R_ANAL_OP_TYPE_MOV) {
			mov_aop = *aop;
		}
		if (aop->type == R_ANAL_OP_TYPE_ADD) {
			add_aop = *aop;
		}
		r_anal_op_fini (aop);
		i += len - 1;
	}
	if (!isValid) {
		return false;
	}

	// check if we have a msvc 19xx style jump table using rva table entries
	// lea reg1, [base_addr]
	// mov reg2, sword [reg1 + tbl_off*4 + tbl_loc_off]
	// add reg2, reg1
	// jmp reg2
	if (mov_aop.type && add_aop.type && mov_aop.addr < add_aop.addr && add_aop.addr < jmp_aop->addr && mov_aop.ptr) {
		// ptr in this case should be tbl_loc_off
		// eprintf ("JMPTBL ADDR %llx\n", mov_aop.ptr);
		*jmptbl_addr += mov_aop.ptr;
	}
#if 0
	// required for the last jmptbl.. but seems to work without it and breaks other tests
	if (mov_aop.type && mov_aop.ptr) {
		*jmptbl_addr += mov_aop.ptr;
		// absjmptbl
		lea_ptr = mov_aop.ptr;
	}
#endif
	/* check if jump table contains valid deltas */
	read_ahead (anal, *jmptbl_addr, (ut8 *)&jmptbl, 64);
	for (i = 0; i < 3; i++) {
		dst = lea_ptr + (st32)r_read_le32 (jmptbl);
		if (!anal->iob.is_valid_offset (anal->iob.io, dst, 0)) {
			return false;
		}
		if (dst > fcn->addr + JMPTBL_MAXFCNSIZE) {
			return false;
		}
		if (anal->opt.jmpabove && dst < (fcn->addr < JMPTBL_MAXFCNSIZE ? 0 : fcn->addr - JMPTBL_MAXFCNSIZE)) {
			return false;
		}
	}
	return true;
}