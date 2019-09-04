#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct spmi_pmic_arb {TYPE_1__* ver_ops; } ;
struct spmi_controller {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* non_data_cmd ) (struct spmi_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPMI_CMD_RESET ; 
 int /*<<< orphan*/  SPMI_CMD_WAKEUP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct spmi_pmic_arb* spmi_controller_get_drvdata (struct spmi_controller*) ; 
 int stub1 (struct spmi_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmic_arb_cmd(struct spmi_controller *ctrl, u8 opc, u8 sid)
{
	struct spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);

	dev_dbg(&ctrl->dev, "cmd op:0x%x sid:%d\n", opc, sid);

	/* Check for valid non-data command */
	if (opc < SPMI_CMD_RESET || opc > SPMI_CMD_WAKEUP)
		return -EINVAL;

	return pmic_arb->ver_ops->non_data_cmd(ctrl, opc, sid);
}