#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_8__ {TYPE_1__* operands; int /*<<< orphan*/  mnemonic; } ;
struct TYPE_7__ {int bits; } ;
struct TYPE_6__ {int type; int reg_size; int reg; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int ALL_SIZE ; 
 int OT_DWORD ; 
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_WORD ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int opbs(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	if (a->bits >= 32 && op->operands[1].type & OT_MEMORY && op->operands[1].reg_size & OT_WORD) {
		return -1;
	}
	if (!(op->operands[1].type & OT_MEMORY) && 
		!((op->operands[0].type & ALL_SIZE) == (op->operands[1].type & ALL_SIZE))) {
		return -1;
	}
	if (op->operands[0].type & OT_GPREG && !(op->operands[0].type & OT_MEMORY)) {
		if (a->bits == 64) {
			if (op->operands[1].type & OT_MEMORY && 
				op->operands[1].reg_size & OT_DWORD) {
				data[l++] = 0x67;
			}
			if (op->operands[0].type & OT_WORD) {
				data[l++] = 0x66;
			}
			if (op->operands[0].type & OT_QWORD) {
				data[l++] = 0x48;
			}
		} else if (op->operands[0].type & OT_WORD) {
				data[l++] = 0x66;
		}
		data[l++] = 0x0f;
		if (!strcmp (op->mnemonic, "bsf")) {
			data[l++] = 0xbc;
		} else {
			data[l++] = 0xbd;
		}
		if (op->operands[1].type & OT_GPREG && !(op->operands[1].type & OT_MEMORY)) {
			data[l] = 0xc0;
		} else if (!(op->operands[1].type & OT_MEMORY)) {
			return -1;
		}
		data[l] += op->operands[0].reg << 3;
		data[l++] += op->operands[1].reg;
	}
	return l;
}