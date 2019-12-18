#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int size; } ;
typedef  TYPE_1__ vle_t ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ vle_handle ;
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  buf_asm ;
struct TYPE_16__ {int /*<<< orphan*/  pc; } ;
struct TYPE_15__ {int size; } ;
typedef  TYPE_3__ RAsmOp ;
typedef  TYPE_4__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vle_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vle_init (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 TYPE_1__* vle_next (TYPE_2__*) ; 
 int /*<<< orphan*/  vle_snprint (char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int decompile_vle(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	vle_t* instr = 0;
	vle_handle handle = {0};
	if (len < 2) {
		return -1;
	}
	if (!vle_init (&handle, buf, len) && (instr = vle_next (&handle))) {
		op->size = instr->size;
		char buf_asm[64];
		vle_snprint (buf_asm, sizeof (buf_asm), a->pc, instr);
		r_asm_op_set_asm (op, buf_asm);
		vle_free (instr);
	} else {
		r_asm_op_set_asm (op, "invalid");
		op->size = 2;
		return -1;
	}
	return op->size;
}