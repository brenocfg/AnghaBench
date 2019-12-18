#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut16 ;
struct TYPE_6__ {scalar_t__ opcode; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  args; } ;
struct TYPE_5__ {int size; int cycles; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;
typedef  scalar_t__ PicMidrangeOpcode ;
typedef  int /*<<< orphan*/  PicMidrangeOpArgsVal ;

/* Variables and functions */
 int PIC_MIDRANGE_OPINFO_LEN ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_ILL ; 
 int /*<<< orphan*/  R_ANAL_OP_TYPE_NOP ; 
 int /*<<< orphan*/  anal_pic_midrange_extract_args (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  anal_pic_midrange_malloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pic_midrange_get_opcode (int /*<<< orphan*/ ) ; 
 TYPE_3__* pic_midrange_op_anal_info ; 
 int /*<<< orphan*/  r_read_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int anal_pic_midrange_op (RAnal *anal, RAnalOp *op, ut64 addr,
				 const ut8 *buf, int len) {

	ut16 instr;
	int i;

	anal_pic_midrange_malloc (anal, false);

	if (!buf || len < 2) {
		op->type = R_ANAL_OP_TYPE_ILL;
		return op->size;
	}

	instr = r_read_le16 (buf);

	// Default op params
	op->size = 2;
	op->cycles = 1;
	op->type = R_ANAL_OP_TYPE_NOP;

	PicMidrangeOpcode opcode = pic_midrange_get_opcode (instr);
	PicMidrangeOpArgsVal args_val;

	for (i = 0; i < PIC_MIDRANGE_OPINFO_LEN; i++) {
		if (pic_midrange_op_anal_info[i].opcode == opcode) {
			anal_pic_midrange_extract_args (
				instr, pic_midrange_op_anal_info[i].args,
				&args_val);
			pic_midrange_op_anal_info[i].handler (anal, op, addr,
							      &args_val);
			break;
		}
	}

	return op->size;
}