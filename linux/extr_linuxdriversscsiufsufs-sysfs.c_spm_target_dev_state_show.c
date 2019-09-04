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
struct ufs_hba {size_t spm_lvl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 struct ufs_hba* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_1__* ufs_pm_lvl_states ; 
 char* ufschd_ufs_dev_pwr_mode_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t spm_target_dev_state_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct ufs_hba *hba = dev_get_drvdata(dev);

	return sprintf(buf, "%s\n", ufschd_ufs_dev_pwr_mode_to_string(
				ufs_pm_lvl_states[hba->spm_lvl].dev_state));
}