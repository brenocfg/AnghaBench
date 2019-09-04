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
struct mdiobb_ops {int (* get_mdio_data ) (struct mdiobb_ctrl*) ;int /*<<< orphan*/  (* set_mdc ) (struct mdiobb_ctrl*,int) ;} ;
struct mdiobb_ctrl {struct mdiobb_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_DELAY ; 
 int /*<<< orphan*/  MDIO_READ_DELAY ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mdiobb_ctrl*,int) ; 
 int /*<<< orphan*/  stub2 (struct mdiobb_ctrl*,int) ; 
 int stub3 (struct mdiobb_ctrl*) ; 

__attribute__((used)) static int mdiobb_get_bit(struct mdiobb_ctrl *ctrl)
{
	const struct mdiobb_ops *ops = ctrl->ops;

	ndelay(MDIO_DELAY);
	ops->set_mdc(ctrl, 1);
	ndelay(MDIO_READ_DELAY);
	ops->set_mdc(ctrl, 0);

	return ops->get_mdio_data(ctrl);
}