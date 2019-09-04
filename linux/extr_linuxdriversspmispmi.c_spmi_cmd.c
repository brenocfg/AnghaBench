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
struct TYPE_2__ {int /*<<< orphan*/ * type; } ;
struct spmi_controller {int (* cmd ) (struct spmi_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spmi_ctrl_type ; 
 int stub1 (struct spmi_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_spmi_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
spmi_cmd(struct spmi_controller *ctrl, u8 opcode, u8 sid)
{
	int ret;

	if (!ctrl || !ctrl->cmd || ctrl->dev.type != &spmi_ctrl_type)
		return -EINVAL;

	ret = ctrl->cmd(ctrl, opcode, sid);
	trace_spmi_cmd(opcode, sid, ret);
	return ret;
}