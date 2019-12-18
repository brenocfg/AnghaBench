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
typedef  size_t PicMidrangeOpcode ;
typedef  int /*<<< orphan*/  PicMidrangeOpInfo ;

/* Variables and functions */
 size_t PIC_MIDRANGE_OPCODE_INVALID ; 
 int /*<<< orphan*/  const* pic_midrange_op_info ; 

const PicMidrangeOpInfo *pic_midrange_get_op_info (PicMidrangeOpcode opcode) {
	if (opcode >= PIC_MIDRANGE_OPCODE_INVALID) {
		return NULL;
	}
	return &pic_midrange_op_info[opcode];
}