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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * type; } ;
struct spmi_controller {int (* write_cmd ) (struct spmi_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spmi_ctrl_type ; 
 int stub1 (struct spmi_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  trace_spmi_write_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  trace_spmi_write_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int spmi_write_cmd(struct spmi_controller *ctrl, u8 opcode,
				 u8 sid, u16 addr, const u8 *buf, size_t len)
{
	int ret;

	if (!ctrl || !ctrl->write_cmd || ctrl->dev.type != &spmi_ctrl_type)
		return -EINVAL;

	trace_spmi_write_begin(opcode, sid, addr, len, buf);
	ret = ctrl->write_cmd(ctrl, opcode, sid, addr, buf, len);
	trace_spmi_write_end(opcode, sid, addr, ret);
	return ret;
}