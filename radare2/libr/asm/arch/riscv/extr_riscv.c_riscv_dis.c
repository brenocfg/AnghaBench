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
typedef  int ut64 ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ insn_t ;
typedef  int /*<<< orphan*/  insn ;
struct TYPE_9__ {int /*<<< orphan*/  bits; } ;
typedef  int /*<<< orphan*/  RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int /*<<< orphan*/  R_MIN (int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  riscv_disassemble (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ ,int) ; 
 int riscv_insn_length (TYPE_1__) ; 

__attribute__((used)) static int riscv_dis(RAsm *a, RAsmOp *rop, const ut8 *buf, ut64 len) {
	insn_t insn = {0};
	if (len < 2) {
		return -1;
	}
	memcpy (&insn, buf, R_MIN (sizeof (insn), len));
	int insn_len = riscv_insn_length(insn);
	if (len < insn_len) {
		return -1;
	}
	riscv_disassemble (a, rop, insn, a->bits, len);
	return insn_len;
}