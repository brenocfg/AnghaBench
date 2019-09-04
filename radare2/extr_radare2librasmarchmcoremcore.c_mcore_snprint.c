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
typedef  int ut32 ;
struct TYPE_6__ {int type; char* name; TYPE_1__* args; } ;
typedef  TYPE_2__ mcore_t ;
struct TYPE_5__ {int value; } ;

/* Variables and functions */
#define  R_ANAL_OP_TYPE_LOAD 129 
#define  R_ANAL_OP_TYPE_STORE 128 
 int* load_shift ; 
 int /*<<< orphan*/  print_loop (char*,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,size_t,size_t,int) ; 

void mcore_snprint(char* str, int size, ut64 addr, mcore_t* instr) {
	ut32 imm;
	if (!instr || !str) {
		return;
	}
	switch (instr->type) {
	case R_ANAL_OP_TYPE_LOAD:
	case R_ANAL_OP_TYPE_STORE:
		imm = instr->args[1].value << load_shift[instr->args[3].value];
		snprintf (str, size, "%s r%u, (r%u, 0x%x)",
			instr->name, instr->args[2].value, instr->args[0].value, imm);
		break;
	default:
		print_loop (str, size, addr, instr);
		break;
	}
}