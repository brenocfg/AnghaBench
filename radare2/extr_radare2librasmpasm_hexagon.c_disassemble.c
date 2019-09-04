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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_6__ {int /*<<< orphan*/  mnem; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ HexInsn ;

/* Variables and functions */
 int hexagon_disasm_instruction (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  r_read_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_strbuf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disassemble (RAsm *a, RAsmOp *op, const ut8 *buf, int l) {
	HexInsn hi = {0};
	ut32 data = r_read_le32 (buf);
	op->size = hexagon_disasm_instruction (data, &hi);
	r_strbuf_set (&op->buf_asm, hi.mnem);
	return op->size;
}