#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* fw; char* dir; } ;
struct TYPE_3__ {TYPE_2__ fw; } ;
struct ath6kl {int /*<<< orphan*/  fw_len; int /*<<< orphan*/ * fw; TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_err (char*,char*,int) ; 
 int ath6kl_get_fw (struct ath6kl*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int ath6kl_fetch_fw_file(struct ath6kl *ar)
{
	char filename[100];
	int ret;

	if (ar->fw != NULL)
		return 0;

	/* FIXME: remove WARN_ON() as we won't support FW API 1 for long */
	if (WARN_ON(ar->hw.fw.fw == NULL))
		return -EINVAL;

	snprintf(filename, sizeof(filename), "%s/%s",
		 ar->hw.fw.dir, ar->hw.fw.fw);

	ret = ath6kl_get_fw(ar, filename, &ar->fw, &ar->fw_len);
	if (ret) {
		ath6kl_err("Failed to get firmware file %s: %d\n",
			   filename, ret);
		return ret;
	}

	return 0;
}