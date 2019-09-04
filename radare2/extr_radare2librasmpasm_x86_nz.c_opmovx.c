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
typedef  int ut8 ;
struct TYPE_6__ {char* mnemonic; TYPE_1__* operands; } ;
struct TYPE_5__ {int type; int reg; int* regs; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_MEMORY ; 
 int OT_REGTYPE ; 
 int OT_WORD ; 
 int X86R_ESP ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_2__ const*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int opmovx(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int word = 0;
	char *movx = op->mnemonic + 3;

	if (!(op->operands[0].type & OT_REGTYPE && op->operands[1].type & OT_MEMORY)) {
		return -1;
	}
	if (op->operands[1].type & OT_WORD) {
		word = 1;
	}

	data[l++] = 0x0f;
	if (!strcmp (movx, "zx")) {
		data[l++] = 0xb6 + word;
	} else if (!strcmp (movx, "sx")) {
		data[l++] = 0xbe + word;
	}
	data[l++] = op->operands[0].reg << 3 | op->operands[1].regs[0];
	if (op->operands[1].regs[0] == X86R_ESP) {
		data[l++] = 0x24;
	}

	return l;
}