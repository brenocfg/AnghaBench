#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int size; int jump; int fail; int ptr; int val; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  RAnalOpMask ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;
typedef  TYPE_2__ HexInsn ;

/* Variables and functions */
 int hexagon_anal_instruction (TYPE_2__*,TYPE_1__*) ; 
 int hexagon_disasm_instruction (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_read_le32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int hexagon_v6_op(RAnal *anal, RAnalOp *op, ut64 addr, const ut8 *buf, int len, RAnalOpMask mask) {
	HexInsn hi = {0};;
	ut32 data = 0;
	memset (op, 0, sizeof (RAnalOp));
	data = r_read_le32 (buf);
	int size = hexagon_disasm_instruction (data, &hi, (ut32) addr);
	op->size = size;
	if (size <= 0) {
		return size;
	}

	op->addr = addr;
	op->jump = op->fail = -1;
	op->ptr = op->val = -1;
	return hexagon_anal_instruction (&hi, op);
}