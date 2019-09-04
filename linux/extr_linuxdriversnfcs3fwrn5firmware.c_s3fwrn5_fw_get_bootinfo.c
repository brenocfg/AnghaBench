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
struct sk_buff {scalar_t__ data; } ;
struct s3fwrn5_fw_info {int dummy; } ;
struct s3fwrn5_fw_header {scalar_t__ code; } ;
struct s3fwrn5_fw_cmd_get_bootinfo_rsp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S3FWRN5_FW_CMD_GET_BOOTINFO ; 
 scalar_t__ S3FWRN5_FW_HDR_SIZE ; 
 int /*<<< orphan*/  S3FWRN5_FW_MSG_CMD ; 
 scalar_t__ S3FWRN5_FW_RET_SUCCESS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct s3fwrn5_fw_cmd_get_bootinfo_rsp*,scalar_t__,int) ; 
 int s3fwrn5_fw_prep_msg (struct s3fwrn5_fw_info*,struct sk_buff**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int s3fwrn5_fw_send_msg (struct s3fwrn5_fw_info*,struct sk_buff*,struct sk_buff**) ; 

__attribute__((used)) static int s3fwrn5_fw_get_bootinfo(struct s3fwrn5_fw_info *fw_info,
	struct s3fwrn5_fw_cmd_get_bootinfo_rsp *bootinfo)
{
	struct sk_buff *msg, *rsp = NULL;
	struct s3fwrn5_fw_header *hdr;
	int ret;

	/* Send GET_BOOTINFO command */

	ret = s3fwrn5_fw_prep_msg(fw_info, &msg, S3FWRN5_FW_MSG_CMD,
		S3FWRN5_FW_CMD_GET_BOOTINFO, NULL, 0);
	if (ret < 0)
		return ret;

	ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
	kfree_skb(msg);
	if (ret < 0)
		return ret;

	hdr = (struct s3fwrn5_fw_header *) rsp->data;
	if (hdr->code != S3FWRN5_FW_RET_SUCCESS) {
		ret = -EINVAL;
		goto out;
	}

	memcpy(bootinfo, rsp->data + S3FWRN5_FW_HDR_SIZE, 10);

out:
	kfree_skb(rsp);
	return ret;
}