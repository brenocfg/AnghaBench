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
struct ufs_hisi_host {int /*<<< orphan*/  rst; struct ufs_hba* hba; } ;
struct ufs_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ufs_hisi_host* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get (struct device*,char*) ; 
 int ufs_hisi_get_resource (struct ufs_hisi_host*) ; 
 int /*<<< orphan*/  ufs_hisi_set_pm_lvl (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_set_variant (struct ufs_hba*,struct ufs_hisi_host*) ; 

__attribute__((used)) static int ufs_hisi_init_common(struct ufs_hba *hba)
{
	int err = 0;
	struct device *dev = hba->dev;
	struct ufs_hisi_host *host;

	host = devm_kzalloc(dev, sizeof(*host), GFP_KERNEL);
	if (!host)
		return -ENOMEM;

	host->hba = hba;
	ufshcd_set_variant(hba, host);

	host->rst  = devm_reset_control_get(dev, "rst");

	ufs_hisi_set_pm_lvl(hba);

	err = ufs_hisi_get_resource(host);
	if (err) {
		ufshcd_set_variant(hba, NULL);
		return err;
	}

	return 0;
}