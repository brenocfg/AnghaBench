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
typedef  int ut8 ;
typedef  int ut32 ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ppcps_t ;
typedef  int /*<<< orphan*/  buf_asm ;
struct TYPE_11__ {int /*<<< orphan*/  pc; } ;
struct TYPE_10__ {int size; } ;
typedef  TYPE_2__ RAsmOp ;
typedef  TYPE_3__ RAsm ;

/* Variables and functions */
 int libps_decode (int const,TYPE_1__*) ; 
 int /*<<< orphan*/  libps_snprint (char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_2__*,char*) ; 

__attribute__((used)) static int decompile_ps(RAsm *a, RAsmOp *op, const ut8 *buf, int len) {
	ppcps_t instr = {0};
	if (len < 4) {
		return -1;
	}
	op->size = 4;
	const ut32 data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	if (libps_decode (data, &instr) < 1) {
		r_asm_op_set_asm (op, "invalid");
		return -1;
	}
	char buf_asm[64];
	libps_snprint (buf_asm, sizeof (buf_asm), a->pc, &instr);
	r_asm_op_set_asm (op, buf_asm);
	return op->size;
}