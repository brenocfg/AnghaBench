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
struct TYPE_3__ {int type; scalar_t__ family; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 scalar_t__ R_ANAL_OP_FAMILY_PRIV ; 
#define  R_ANAL_OP_TYPE_CALL 135 
#define  R_ANAL_OP_TYPE_CJMP 134 
#define  R_ANAL_OP_TYPE_ILL 133 
#define  R_ANAL_OP_TYPE_JMP 132 
#define  R_ANAL_OP_TYPE_RCALL 131 
#define  R_ANAL_OP_TYPE_SWI 130 
#define  R_ANAL_OP_TYPE_TRAP 129 
#define  R_ANAL_OP_TYPE_UCALL 128 

__attribute__((used)) static bool checkAnalType(RAnalOp *op, int t) {
	if (t == 'c') {
		switch (op->type) {
		case R_ANAL_OP_TYPE_RCALL:
		case R_ANAL_OP_TYPE_UCALL:
		case R_ANAL_OP_TYPE_CALL:
			return true;
		}
	} else if (t == 's') {
		if (op->family == R_ANAL_OP_FAMILY_PRIV) {
			return true;
		}
		switch (op->type) {
		case R_ANAL_OP_TYPE_SWI:
			return true;
		}
	} else if (t == 'i') {
		switch (op->type) {
		case R_ANAL_OP_TYPE_TRAP:
		case R_ANAL_OP_TYPE_ILL:
			return true;
		}
	} else if (t == 'j') {
		switch (op->type) {
		case R_ANAL_OP_TYPE_JMP:
		//case R_ANAL_OP_TYPE_RJMP:
		//case R_ANAL_OP_TYPE_UJMP:
		case R_ANAL_OP_TYPE_CJMP:
			return true;
		}
	}
	return false;
}