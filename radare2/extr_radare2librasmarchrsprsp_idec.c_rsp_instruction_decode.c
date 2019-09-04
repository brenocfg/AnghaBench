#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_5__ {int noperands; int /*<<< orphan*/ * odecs; int /*<<< orphan*/  opcode; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_1__ rsp_instruction_priv ;
struct TYPE_6__ {int noperands; int /*<<< orphan*/ * operands; int /*<<< orphan*/  opcode; int /*<<< orphan*/  mnemonic; } ;
typedef  TYPE_2__ rsp_instruction ;

/* Variables and functions */
 TYPE_1__* rsp_decode_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsp_operand_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

rsp_instruction rsp_instruction_decode(ut64 pc, ut32 iw) {
	int opnd;
	const rsp_instruction_priv* priv = rsp_decode_priv (iw);

	rsp_instruction r_instr;

	r_instr.mnemonic = priv->mnemonic;
	r_instr.opcode = priv->opcode;
	r_instr.noperands = priv->noperands;
	for (opnd = 0; opnd < r_instr.noperands; ++opnd) {
		r_instr.operands[opnd] = rsp_operand_decode (pc, iw, &priv->odecs[opnd]);
	}

	return r_instr;
}