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
struct intel_sst_drv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPC_CMD ; 
 int /*<<< orphan*/  IPC_PREP_D3 ; 
 int /*<<< orphan*/  PIPE_RSVD ; 
 int /*<<< orphan*/  SST_TASK_ID_MEDIA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sst_prepare_and_post_msg (struct intel_sst_drv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static int sst_save_dsp_context_v2(struct intel_sst_drv *sst)
{
	int ret = 0;

	ret = sst_prepare_and_post_msg(sst, SST_TASK_ID_MEDIA, IPC_CMD,
			IPC_PREP_D3, PIPE_RSVD, 0, NULL, NULL,
			true, true, false, true);

	if (ret < 0) {
		dev_err(sst->dev, "not suspending FW!!, Err: %d\n", ret);
		return -EIO;
	}

	return 0;
}