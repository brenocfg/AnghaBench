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
typedef  int /*<<< orphan*/  u8 ;
struct mdiobb_ops {int /*<<< orphan*/  (* set_mdio_dir ) (struct mdiobb_ctrl*,int) ;} ;
struct mdiobb_ctrl {struct mdiobb_ops* ops; } ;

/* Variables and functions */
 int MDIO_C45 ; 
 int /*<<< orphan*/  mdiobb_send_bit (struct mdiobb_ctrl*,int) ; 
 int /*<<< orphan*/  mdiobb_send_num (struct mdiobb_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct mdiobb_ctrl*,int) ; 

__attribute__((used)) static void mdiobb_cmd(struct mdiobb_ctrl *ctrl, int op, u8 phy, u8 reg)
{
	const struct mdiobb_ops *ops = ctrl->ops;
	int i;

	ops->set_mdio_dir(ctrl, 1);

	/*
	 * Send a 32 bit preamble ('1's) with an extra '1' bit for good
	 * measure.  The IEEE spec says this is a PHY optional
	 * requirement.  The AMD 79C874 requires one after power up and
	 * one after a MII communications error.  This means that we are
	 * doing more preambles than we need, but it is safer and will be
	 * much more robust.
	 */

	for (i = 0; i < 32; i++)
		mdiobb_send_bit(ctrl, 1);

	/* send the start bit (01) and the read opcode (10) or write (01).
	   Clause 45 operation uses 00 for the start and 11, 10 for
	   read/write */
	mdiobb_send_bit(ctrl, 0);
	if (op & MDIO_C45)
		mdiobb_send_bit(ctrl, 0);
	else
		mdiobb_send_bit(ctrl, 1);
	mdiobb_send_bit(ctrl, (op >> 1) & 1);
	mdiobb_send_bit(ctrl, (op >> 0) & 1);

	mdiobb_send_num(ctrl, phy, 5);
	mdiobb_send_num(ctrl, reg, 5);
}