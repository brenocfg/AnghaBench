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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int size; int /*<<< orphan*/  buf_asm; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  int /*<<< orphan*/  RAsm ;

/* Variables and functions */
 int R_MAX (int /*<<< orphan*/ ,int) ; 
 int i8080_disasm (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_strbuf_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	int dlen = i8080_disasm (buf, r_strbuf_get (&op->buf_asm), len);
	return op->size = R_MAX (0, dlen);
}