#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ size; } ;
struct TYPE_10__ {scalar_t__ offset; TYPE_1__* print; } ;
struct TYPE_9__ {scalar_t__ cur; } ;
typedef  TYPE_1__ RPrint ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_MASK_BASIC ; 
 int /*<<< orphan*/  __fix_cursor_down (TYPE_2__*) ; 
 int /*<<< orphan*/  r_anal_op_free (TYPE_3__*) ; 
 TYPE_3__* r_core_anal_op (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

void __cursor_down(RCore *core) {
	RPrint *print = core->print;
	RAnalOp *aop = r_core_anal_op (core, core->offset + print->cur, R_ANAL_OP_MASK_BASIC);
	if (aop) {
		print->cur += aop->size;
		r_anal_op_free (aop);
	} else {
		print->cur += 4;
	}
	__fix_cursor_down (core);
}