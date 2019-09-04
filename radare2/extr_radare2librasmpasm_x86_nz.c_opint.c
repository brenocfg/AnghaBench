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
typedef  int st32 ;
struct TYPE_5__ {TYPE_1__* operands; } ;
struct TYPE_4__ {int type; int immediate; int sign; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_CONSTANT ; 

__attribute__((used)) static int opint(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	if (op->operands[0].type & OT_CONSTANT) {
		st32 immediate = op->operands[0].immediate * op->operands[0].sign;
		if (immediate <= 255 && immediate >= -128) {
			data[l++] = 0xcd;
			data[l++] = immediate;
		}
	}
	return l;
}