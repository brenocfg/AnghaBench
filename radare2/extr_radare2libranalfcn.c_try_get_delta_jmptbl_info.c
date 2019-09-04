#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct TYPE_7__ {int /*<<< orphan*/  io; int /*<<< orphan*/  (* read_at ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_9__ {TYPE_1__ iob; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__ jump; scalar_t__ fail; int val; int refptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnalFunction ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 scalar_t__ R_ANAL_OP_TYPE_CJMP ; 
 scalar_t__ R_ANAL_OP_TYPE_CMP ; 
 scalar_t__ R_ANAL_OP_TYPE_MASK ; 
 int UT64_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int r_anal_op (TYPE_3__*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool try_get_delta_jmptbl_info(RAnal *anal, RAnalFunction *fcn, ut64 jmp_addr, ut64 lea_addr, ut64 *table_size, ut64 *default_case) {
	bool isValid = false;
	bool foundCmp = false;
	int i;

	RAnalOp tmp_aop = {0};
	if (lea_addr > jmp_addr) {
		return false;
	}
	int search_sz = jmp_addr - lea_addr;
	ut8 *buf = malloc (search_sz);
	if (!buf) {
		return false;
	}
	// search for a cmp register with a resonable size
	anal->iob.read_at (anal->iob.io, lea_addr, (ut8 *)buf, search_sz);

	for (i = 0; i + 8 < search_sz; i++) {
		int len = r_anal_op (anal, &tmp_aop, lea_addr + i, buf + i, search_sz - i, R_ANAL_OP_MASK_BASIC);
		if (len < 1) {
			len = 1;
		}

		if (foundCmp) {
			if (tmp_aop.type != R_ANAL_OP_TYPE_CJMP) {
				continue;
			}

			*default_case = tmp_aop.jump == tmp_aop.jump + len ? tmp_aop.fail : tmp_aop.jump;
			break;
		}

		ut32 type = tmp_aop.type & R_ANAL_OP_TYPE_MASK;
		if (type != R_ANAL_OP_TYPE_CMP) {
			continue;
		}
		// get the value of the cmp
		// for operands in op, check if type is immediate and val is sane
		// TODO: How? opex?

		// for the time being, this seems to work
		// might not actually have a value, let the next step figure out the size then
		if (tmp_aop.val == UT64_MAX && tmp_aop.refptr == 0) {
			isValid = true;
			*table_size = 0;
		} else if (tmp_aop.refptr == 0) {
			isValid = tmp_aop.val < 0x200;
			*table_size = tmp_aop.val + 1;
		} else {
			isValid = tmp_aop.refptr < 0x200;
			*table_size = tmp_aop.refptr + 1;
		}
		// TODO: check the jmp for whether val is included in valid range or not (ja vs jae)
		foundCmp = true;
	}
	free (buf);
	return isValid;
}