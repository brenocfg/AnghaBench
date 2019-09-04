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
struct s3fwrn5_info {int /*<<< orphan*/  ndev; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3FWRN5_MODE_NCI ; 
 int nci_core_init (int /*<<< orphan*/ ) ; 
 int nci_core_reset (int /*<<< orphan*/ ) ; 
 struct s3fwrn5_info* nci_get_drvdata (struct nci_dev*) ; 
 int s3fwrn5_firmware_update (struct s3fwrn5_info*) ; 
 int /*<<< orphan*/  s3fwrn5_set_mode (struct s3fwrn5_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3fwrn5_set_wake (struct s3fwrn5_info*,int) ; 

__attribute__((used)) static int s3fwrn5_nci_post_setup(struct nci_dev *ndev)
{
	struct s3fwrn5_info *info = nci_get_drvdata(ndev);
	int ret;

	ret = s3fwrn5_firmware_update(info);
	if (ret < 0)
		goto out;

	/* NCI core reset */

	s3fwrn5_set_mode(info, S3FWRN5_MODE_NCI);
	s3fwrn5_set_wake(info, true);

	ret = nci_core_reset(info->ndev);
	if (ret < 0)
		goto out;

	ret = nci_core_init(info->ndev);

out:
	return ret;
}