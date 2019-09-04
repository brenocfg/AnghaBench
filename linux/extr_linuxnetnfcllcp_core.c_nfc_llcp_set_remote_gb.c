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
typedef  int u8 ;
struct nfc_llcp_local {int remote_gb_len; int /*<<< orphan*/ * remote_gb; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int NFC_MAX_GT_LEN ; 
 int /*<<< orphan*/  llcp_magic ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct nfc_llcp_local* nfc_llcp_find_local (struct nfc_dev*) ; 
 int nfc_llcp_parse_gb_tlv (struct nfc_llcp_local*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int nfc_llcp_set_remote_gb(struct nfc_dev *dev, u8 *gb, u8 gb_len)
{
	struct nfc_llcp_local *local;

	if (gb_len < 3 || gb_len > NFC_MAX_GT_LEN)
		return -EINVAL;

	local = nfc_llcp_find_local(dev);
	if (local == NULL) {
		pr_err("No LLCP device\n");
		return -ENODEV;
	}

	memset(local->remote_gb, 0, NFC_MAX_GT_LEN);
	memcpy(local->remote_gb, gb, gb_len);
	local->remote_gb_len = gb_len;

	if (memcmp(local->remote_gb, llcp_magic, 3)) {
		pr_err("MAC does not support LLCP\n");
		return -EINVAL;
	}

	return nfc_llcp_parse_gb_tlv(local,
				     &local->remote_gb[3],
				     local->remote_gb_len - 3);
}