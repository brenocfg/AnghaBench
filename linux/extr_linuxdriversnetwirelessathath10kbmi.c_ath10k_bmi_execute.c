#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  result; } ;
union bmi_resp {TYPE_3__ execute; } ;
typedef  int u32 ;
struct TYPE_5__ {void* param; void* addr; } ;
struct bmi_cmd {TYPE_2__ execute; void* id; } ;
struct TYPE_4__ {scalar_t__ done_sent; } ;
struct ath10k {TYPE_1__ bmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BMI ; 
 int BMI_EXECUTE ; 
 int EBUSY ; 
 int EIO ; 
 void* __cpu_to_le32 (int) ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,...) ; 
 int ath10k_hif_exchange_bmi_msg (struct ath10k*,struct bmi_cmd*,int,union bmi_resp*,int*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 

int ath10k_bmi_execute(struct ath10k *ar, u32 address, u32 param, u32 *result)
{
	struct bmi_cmd cmd;
	union bmi_resp resp;
	u32 cmdlen = sizeof(cmd.id) + sizeof(cmd.execute);
	u32 resplen = sizeof(resp.execute);
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi execute address 0x%x param 0x%x\n",
		   address, param);

	if (ar->bmi.done_sent) {
		ath10k_warn(ar, "command disallowed\n");
		return -EBUSY;
	}

	cmd.id            = __cpu_to_le32(BMI_EXECUTE);
	cmd.execute.addr  = __cpu_to_le32(address);
	cmd.execute.param = __cpu_to_le32(param);

	ret = ath10k_hif_exchange_bmi_msg(ar, &cmd, cmdlen, &resp, &resplen);
	if (ret) {
		ath10k_warn(ar, "unable to read from the device\n");
		return ret;
	}

	if (resplen < sizeof(resp.execute)) {
		ath10k_warn(ar, "invalid execute response length (%d)\n",
			    resplen);
		return -EIO;
	}

	*result = __le32_to_cpu(resp.execute.result);

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi execute result 0x%x\n", *result);

	return 0;
}