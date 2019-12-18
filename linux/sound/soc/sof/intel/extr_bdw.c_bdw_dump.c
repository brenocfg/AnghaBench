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
typedef  int /*<<< orphan*/  u32 ;
struct sof_ipc_panic_info {int dummy; } ;
struct sof_ipc_dsp_oops_xtensa {int dummy; } ;
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDW_DSP_BAR ; 
 int BDW_STACK_DUMP_SIZE ; 
 int /*<<< orphan*/  SHIM_IPCD ; 
 int /*<<< orphan*/  SHIM_IPCX ; 
 int /*<<< orphan*/  bdw_get_registers (struct snd_sof_dev*,struct sof_ipc_dsp_oops_xtensa*,struct sof_ipc_panic_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_get_status (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sof_ipc_dsp_oops_xtensa*,struct sof_ipc_panic_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bdw_dump(struct snd_sof_dev *sdev, u32 flags)
{
	struct sof_ipc_dsp_oops_xtensa xoops;
	struct sof_ipc_panic_info panic_info;
	u32 stack[BDW_STACK_DUMP_SIZE];
	u32 status, panic;

	/* now try generic SOF status messages */
	status = snd_sof_dsp_read(sdev, BDW_DSP_BAR, SHIM_IPCD);
	panic = snd_sof_dsp_read(sdev, BDW_DSP_BAR, SHIM_IPCX);
	bdw_get_registers(sdev, &xoops, &panic_info, stack,
			  BDW_STACK_DUMP_SIZE);
	snd_sof_get_status(sdev, status, panic, &xoops, &panic_info, stack,
			   BDW_STACK_DUMP_SIZE);
}