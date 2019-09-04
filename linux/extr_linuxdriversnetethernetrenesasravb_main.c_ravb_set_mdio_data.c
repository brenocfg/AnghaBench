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
struct mdiobb_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIR_MDO ; 
 int /*<<< orphan*/  ravb_mdio_ctrl (struct mdiobb_ctrl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ravb_set_mdio_data(struct mdiobb_ctrl *ctrl, int value)
{
	ravb_mdio_ctrl(ctrl, PIR_MDO, value);
}