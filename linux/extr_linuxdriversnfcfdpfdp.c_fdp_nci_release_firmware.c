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
struct nci_dev {int dummy; } ;
struct fdp_nci_info {int /*<<< orphan*/ * ram_patch; int /*<<< orphan*/ * otp_patch; } ;

/* Variables and functions */
 struct fdp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fdp_nci_release_firmware(struct nci_dev *ndev)
{
	struct fdp_nci_info *info = nci_get_drvdata(ndev);

	if (info->otp_patch) {
		release_firmware(info->otp_patch);
		info->otp_patch = NULL;
	}

	if (info->ram_patch) {
		release_firmware(info->ram_patch);
		info->ram_patch = NULL;
	}
}