#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t PicBaselineOpcode ;
typedef  int /*<<< orphan*/  PicBaselineOpInfo ;

/* Variables and functions */
 size_t PIC_BASELINE_OPCODE_INVALID ; 
 int /*<<< orphan*/  const* pic_baseline_op_info ; 

const PicBaselineOpInfo *pic_baseline_get_op_info(PicBaselineOpcode opcode) {
	if (opcode >= PIC_BASELINE_OPCODE_INVALID) {
		return NULL;
	}
	return &pic_baseline_op_info[opcode];
}