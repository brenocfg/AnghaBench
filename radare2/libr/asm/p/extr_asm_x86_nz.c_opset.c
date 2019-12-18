#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_5__ {TYPE_1__* operands; int /*<<< orphan*/  mnemonic; } ;
struct TYPE_4__ {int type; int* regs; int reg; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int opset(RAsm *a, ut8 *data, const Opcode *op) {
	if (!(op->operands[0].type & (OT_GPREG | OT_BYTE))) {return -1;}
	int l = 0;
	int mod = 0;
	int reg = op->operands[0].regs[0];

	data[l++] = 0x0f;
	if (!strcmp (op->mnemonic, "seto")) {
		data[l++] = 0x90;
	} else if (!strcmp (op->mnemonic, "setno")) {
		data[l++] = 0x91;
	} else if (!strcmp (op->mnemonic, "setb") ||
			  !strcmp (op->mnemonic, "setnae") ||
			  !strcmp (op->mnemonic, "setc")) {
		data[l++] = 0x92;
	} else if (!strcmp (op->mnemonic, "setnb") ||
			   !strcmp (op->mnemonic, "setae") ||
			   !strcmp (op->mnemonic, "setnc")) {
		data[l++] = 0x93;
	} else if (!strcmp (op->mnemonic, "setz") ||
			   !strcmp (op->mnemonic, "sete")) {
		data[l++] = 0x94;
	} else if (!strcmp (op->mnemonic, "setnz") ||
			   !strcmp (op->mnemonic, "setne")) {
		data[l++] = 0x95;
	} else if (!strcmp (op->mnemonic, "setbe") ||
			   !strcmp (op->mnemonic, "setna")) {
		data[l++] = 0x96;
	} else if (!strcmp (op->mnemonic, "setnbe") ||
			   !strcmp (op->mnemonic, "seta")) {
		data[l++] = 0x97;
	} else if (!strcmp (op->mnemonic, "sets")) {
		data[l++] = 0x98;
	} else if (!strcmp (op->mnemonic, "setns")) {
		data[l++] = 0x99;
	} else if (!strcmp (op->mnemonic, "setp") ||
			   !strcmp (op->mnemonic, "setpe")) {
		data[l++] = 0x9a;
	} else if (!strcmp (op->mnemonic, "setnp") ||
			   !strcmp (op->mnemonic, "setpo")) {
		data[l++] = 0x9b;
	} else if (!strcmp (op->mnemonic, "setl") ||
			   !strcmp (op->mnemonic, "setnge")) {
		data[l++] = 0x9c;
	} else if (!strcmp (op->mnemonic, "setnl") ||
			   !strcmp (op->mnemonic, "setge")) {
		data[l++] = 0x9d;
	} else if (!strcmp (op->mnemonic, "setle") ||
			   !strcmp (op->mnemonic, "setng")) {
		data[l++] = 0x9e;
	} else if (!strcmp (op->mnemonic, "setnle") ||
			   !strcmp (op->mnemonic, "setg")) {
		data[l++] = 0x9f;
	} else {
		return -1;
	}
	if (!(op->operands[0].type & OT_MEMORY)) {
		mod = 3;
		reg = op->operands[0].reg;
	}
	data[l++] = mod << 6 | reg;
	return l;
}