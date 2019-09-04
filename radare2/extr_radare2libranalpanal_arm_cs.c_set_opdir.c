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
struct TYPE_3__ {int type; int /*<<< orphan*/  direction; } ;
typedef  TYPE_1__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_OP_DIR_EXEC ; 
 int /*<<< orphan*/  R_ANAL_OP_DIR_READ ; 
 int /*<<< orphan*/  R_ANAL_OP_DIR_REF ; 
 int /*<<< orphan*/  R_ANAL_OP_DIR_WRITE ; 
#define  R_ANAL_OP_TYPE_CALL 134 
#define  R_ANAL_OP_TYPE_JMP 133 
#define  R_ANAL_OP_TYPE_LEA 132 
#define  R_ANAL_OP_TYPE_LOAD 131 
 int R_ANAL_OP_TYPE_MASK ; 
#define  R_ANAL_OP_TYPE_STORE 130 
#define  R_ANAL_OP_TYPE_UCALL 129 
#define  R_ANAL_OP_TYPE_UJMP 128 

__attribute__((used)) static void set_opdir(RAnalOp *op) {
	switch (op->type & R_ANAL_OP_TYPE_MASK) {
	case R_ANAL_OP_TYPE_LOAD:
		op->direction = R_ANAL_OP_DIR_READ;
		break;
	case R_ANAL_OP_TYPE_STORE:
		op->direction = R_ANAL_OP_DIR_WRITE;
		break;
	case R_ANAL_OP_TYPE_LEA:
		op->direction = R_ANAL_OP_DIR_REF;
		break;
	case R_ANAL_OP_TYPE_CALL:
	case R_ANAL_OP_TYPE_JMP:
	case R_ANAL_OP_TYPE_UJMP:
	case R_ANAL_OP_TYPE_UCALL:
		op->direction = R_ANAL_OP_DIR_EXEC;
		break;
	default:
		break;
        }
}