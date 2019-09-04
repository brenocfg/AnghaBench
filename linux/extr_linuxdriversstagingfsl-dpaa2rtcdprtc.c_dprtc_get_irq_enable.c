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
struct dprtc_rsp_get_irq_enable {int /*<<< orphan*/  en; } ;
struct dprtc_cmd_get_irq {int /*<<< orphan*/  irq_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRTC_CMDID_GET_IRQ_ENABLE ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dprtc_get_irq_enable(struct fsl_mc_io *mc_io,
			 u32 cmd_flags,
			 u16 token,
			 u8 irq_index,
			 u8 *en)
{
	struct dprtc_rsp_get_irq_enable *rsp_params;
	struct dprtc_cmd_get_irq *cmd_params;
	struct fsl_mc_command cmd = { 0 };
	int err;

	cmd.header = mc_encode_cmd_header(DPRTC_CMDID_GET_IRQ_ENABLE,
					  cmd_flags,
					  token);
	cmd_params = (struct dprtc_cmd_get_irq *)cmd.params;
	cmd_params->irq_index = irq_index;

	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dprtc_rsp_get_irq_enable *)cmd.params;
	*en = rsp_params->en;

	return 0;
}