#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_7__ {int /*<<< orphan*/  pc; } ;
struct TYPE_6__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int R_MAX (int,int /*<<< orphan*/ ) ; 
 int _6502Disass (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int disassemble(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	int dlen = _6502Disass (a->pc, op, buf, len);
	return op->size = R_MAX (dlen, 0);
}