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
struct TYPE_3__ {int refptr; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ILL ; 

__attribute__((used)) static void map_zz2refptr(RAnalOp *op, ut8 mode_zz) {
	switch (mode_zz) {
	case 0: op->refptr = 4; break;
	case 1: op->refptr = 1; break;
	case 2: op->refptr = 2; break;
	default:
		op->type = R_ANAL_OP_TYPE_ILL;
		break;
	}
}