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
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int disable_host_v3_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  hisi_sas_init_mem (struct hisi_hba*) ; 
 int hw_init_v3_hw (struct hisi_hba*) ; 

__attribute__((used)) static int soft_reset_v3_hw(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	int rc;

	rc = disable_host_v3_hw(hisi_hba);
	if (rc) {
		dev_err(dev, "soft reset: disable host failed rc=%d\n", rc);
		return rc;
	}

	hisi_sas_init_mem(hisi_hba);

	return hw_init_v3_hw(hisi_hba);
}