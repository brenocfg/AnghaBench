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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpni_cmd_set_irq_enable {int /*<<< orphan*/  irq_index; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_CMDID_SET_IRQ_ENABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  dpni_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpni_set_irq_enable(struct fsl_mc_io *mc_io,
			u32 cmd_flags,
			u16 token,
			u8 irq_index,
			u8 en)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpni_cmd_set_irq_enable *cmd_params;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPNI_CMDID_SET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (struct dpni_cmd_set_irq_enable *)cmd.params;
	dpni_set_field(cmd_params->enable, ENABLE, en);
	cmd_params->irq_index = irq_index;

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}