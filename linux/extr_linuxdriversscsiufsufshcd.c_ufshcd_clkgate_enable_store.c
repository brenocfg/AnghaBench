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
typedef  int u32 ;
struct TYPE_4__ {int is_enabled; int /*<<< orphan*/  active_reqs; } ;
struct ufs_hba {TYPE_2__ clk_gating; TYPE_1__* host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 size_t EINVAL ; 
 struct ufs_hba* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtou32 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ufshcd_release (struct ufs_hba*) ; 

__attribute__((used)) static ssize_t ufshcd_clkgate_enable_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct ufs_hba *hba = dev_get_drvdata(dev);
	unsigned long flags;
	u32 value;

	if (kstrtou32(buf, 0, &value))
		return -EINVAL;

	value = !!value;
	if (value == hba->clk_gating.is_enabled)
		goto out;

	if (value) {
		ufshcd_release(hba);
	} else {
		spin_lock_irqsave(hba->host->host_lock, flags);
		hba->clk_gating.active_reqs++;
		spin_unlock_irqrestore(hba->host->host_lock, flags);
	}

	hba->clk_gating.is_enabled = value;
out:
	return count;
}