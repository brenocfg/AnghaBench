#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_10__ {scalar_t__ cpu; } ;
struct TYPE_9__ {int size; } ;
typedef  TYPE_1__ RAsmOp ;
typedef  TYPE_2__ RAsm ;

/* Variables and functions */
 int pic_baseline_disassemble (TYPE_1__*,char*,int /*<<< orphan*/  const*,int) ; 
 int pic_midrange_disassemble (TYPE_1__*,char*,int /*<<< orphan*/  const*,int) ; 
 int pic_pic18_disassemble (TYPE_1__*,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_asm_op_set_asm (TYPE_1__*,char const*) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int asm_pic_disassemble(RAsm *a, RAsmOp *op, const ut8 *b, int l) {
	int res = -1;
	char opbuf[128];
	const char *opstr = opbuf;
	strcpy (opbuf, "invalid");
	if (a->cpu && strcasecmp (a->cpu, "baseline") == 0) {
		res = pic_baseline_disassemble (op, opbuf, b, l);
	} else if (a->cpu && strcasecmp (a->cpu, "midrange") == 0) {
		res = pic_midrange_disassemble (op, opbuf, b, l);
	} else if (a->cpu && strcasecmp (a->cpu, "pic18") == 0) {
		res = pic_pic18_disassemble (op, opbuf, b, l);
	}
	r_asm_op_set_asm (op, opstr);
	return op->size = res;
}