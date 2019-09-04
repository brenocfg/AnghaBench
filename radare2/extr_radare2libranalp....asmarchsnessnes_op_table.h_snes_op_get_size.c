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
struct TYPE_3__ {int len; } ;
typedef  TYPE_1__ snes_op_t ;

/* Variables and functions */
 int SNES_OP_16BIT ; 
 int SNES_OP_24BIT ; 
#define  SNES_OP_IMM_M 129 
#define  SNES_OP_IMM_X 128 

__attribute__((used)) static int snes_op_get_size(int M_flag, int X_flag, snes_op_t* op) {

	switch(op->len) {
		case SNES_OP_IMM_M: return M_flag ? SNES_OP_16BIT : SNES_OP_24BIT;
		case SNES_OP_IMM_X: return X_flag ? SNES_OP_16BIT : SNES_OP_24BIT;
		default: return op->len;
	}
}