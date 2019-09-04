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
struct ipr_ioa_cfg {unsigned long iopoll_weight; int nvectors; int hrrq_num; TYPE_2__* hrrq; scalar_t__ sis64; TYPE_1__* pdev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  iopoll; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ipr_iopoll ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_poll_init (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static ssize_t ipr_store_iopoll_weight(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)shost->hostdata;
	unsigned long user_iopoll_weight;
	unsigned long lock_flags = 0;
	int i;

	if (!ioa_cfg->sis64) {
		dev_info(&ioa_cfg->pdev->dev, "irq_poll not supported on this adapter\n");
		return -EINVAL;
	}
	if (kstrtoul(buf, 10, &user_iopoll_weight))
		return -EINVAL;

	if (user_iopoll_weight > 256) {
		dev_info(&ioa_cfg->pdev->dev, "Invalid irq_poll weight. It must be less than 256\n");
		return -EINVAL;
	}

	if (user_iopoll_weight == ioa_cfg->iopoll_weight) {
		dev_info(&ioa_cfg->pdev->dev, "Current irq_poll weight has the same weight\n");
		return strlen(buf);
	}

	if (ioa_cfg->iopoll_weight && ioa_cfg->sis64 && ioa_cfg->nvectors > 1) {
		for (i = 1; i < ioa_cfg->hrrq_num; i++)
			irq_poll_disable(&ioa_cfg->hrrq[i].iopoll);
	}

	spin_lock_irqsave(shost->host_lock, lock_flags);
	ioa_cfg->iopoll_weight = user_iopoll_weight;
	if (ioa_cfg->iopoll_weight && ioa_cfg->sis64 && ioa_cfg->nvectors > 1) {
		for (i = 1; i < ioa_cfg->hrrq_num; i++) {
			irq_poll_init(&ioa_cfg->hrrq[i].iopoll,
					ioa_cfg->iopoll_weight, ipr_iopoll);
		}
	}
	spin_unlock_irqrestore(shost->host_lock, lock_flags);

	return strlen(buf);
}