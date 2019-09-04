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
struct TYPE_3__ {void* jump; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 void* GB_IB_DST (int const,int const,int /*<<< orphan*/ ) ; 
 scalar_t__ GB_IS_RAM_DST (int const,int const) ; 
 int /*<<< orphan*/  GB_IS_VBANK_DST (int const,int const) ; 
 void* GB_SOFTCAST (int const,int const) ; 
 int /*<<< orphan*/  R_META_TYPE_COMMENT ; 
 int /*<<< orphan*/  r_meta_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ut8 gb_op_calljump(RAnal *a, RAnalOp *op, const ut8 *data, ut64 addr)
{
	if (GB_IS_RAM_DST (data[1],data[2])) {
		op->jump = GB_SOFTCAST (data[1], data[2]);
		r_meta_set_string (a, R_META_TYPE_COMMENT, addr, "--> unpredictable");
		return false;
	}
	if (!GB_IS_VBANK_DST (data[1], data[2])) {
		op->jump = GB_SOFTCAST(data[1], data[2]);
	} else {
		op->jump = GB_IB_DST (data[1], data[2], addr);
	}
	return true;
}