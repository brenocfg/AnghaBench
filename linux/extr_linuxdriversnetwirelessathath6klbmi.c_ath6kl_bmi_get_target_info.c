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
typedef  int /*<<< orphan*/  u32 ;
struct ath6kl_bmi_target_info {int /*<<< orphan*/  type; int /*<<< orphan*/  version; int /*<<< orphan*/  byte_count; } ;
struct TYPE_2__ {scalar_t__ done_sent; } ;
struct ath6kl {scalar_t__ hif_type; TYPE_1__ bmi; } ;
typedef  int /*<<< orphan*/  cid ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BMI ; 
 scalar_t__ ATH6KL_HIF_TYPE_USB ; 
 int /*<<< orphan*/  BMI_GET_TARGET_INFO ; 
 int EACCES ; 
 int EINVAL ; 
 int TARGET_VERSION_SENTINAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int,...) ; 
 int ath6kl_hif_bmi_read (struct ath6kl*,int /*<<< orphan*/ *,int) ; 
 int ath6kl_hif_bmi_write (struct ath6kl*,int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

int ath6kl_bmi_get_target_info(struct ath6kl *ar,
			       struct ath6kl_bmi_target_info *targ_info)
{
	int ret;
	u32 cid = BMI_GET_TARGET_INFO;

	if (ar->bmi.done_sent) {
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		return -EACCES;
	}

	ret = ath6kl_hif_bmi_write(ar, (u8 *)&cid, sizeof(cid));
	if (ret) {
		ath6kl_err("Unable to send get target info: %d\n", ret);
		return ret;
	}

	if (ar->hif_type == ATH6KL_HIF_TYPE_USB) {
		ret = ath6kl_hif_bmi_read(ar, (u8 *)targ_info,
					  sizeof(*targ_info));
	} else {
		ret = ath6kl_hif_bmi_read(ar, (u8 *)&targ_info->version,
				sizeof(targ_info->version));
	}

	if (ret) {
		ath6kl_err("Unable to recv target info: %d\n", ret);
		return ret;
	}

	if (le32_to_cpu(targ_info->version) == TARGET_VERSION_SENTINAL) {
		/* Determine how many bytes are in the Target's targ_info */
		ret = ath6kl_hif_bmi_read(ar,
				   (u8 *)&targ_info->byte_count,
				   sizeof(targ_info->byte_count));
		if (ret) {
			ath6kl_err("unable to read target info byte count: %d\n",
				   ret);
			return ret;
		}

		/*
		 * The target's targ_info doesn't match the host's targ_info.
		 * We need to do some backwards compatibility to make this work.
		 */
		if (le32_to_cpu(targ_info->byte_count) != sizeof(*targ_info)) {
			WARN_ON(1);
			return -EINVAL;
		}

		/* Read the remainder of the targ_info */
		ret = ath6kl_hif_bmi_read(ar,
				   ((u8 *)targ_info) +
				   sizeof(targ_info->byte_count),
				   sizeof(*targ_info) -
				   sizeof(targ_info->byte_count));

		if (ret) {
			ath6kl_err("Unable to read target info (%d bytes): %d\n",
				   targ_info->byte_count, ret);
			return ret;
		}
	}

	ath6kl_dbg(ATH6KL_DBG_BMI, "target info (ver: 0x%x type: 0x%x)\n",
		   targ_info->version, targ_info->type);

	return 0;
}