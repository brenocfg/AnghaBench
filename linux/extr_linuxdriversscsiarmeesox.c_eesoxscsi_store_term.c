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
struct expansion_card {int dummy; } ;
struct eesoxscsi_info {int /*<<< orphan*/  ctl_port; int /*<<< orphan*/  control; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; scalar_t__ hostdata; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct expansion_card* ECARD_DEV (struct device*) ; 
 int /*<<< orphan*/  EESOX_TERM_ENABLE ; 
 struct Scsi_Host* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t eesoxscsi_store_term(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
{
	struct expansion_card *ec = ECARD_DEV(dev);
	struct Scsi_Host *host = ecard_get_drvdata(ec);
	struct eesoxscsi_info *info = (struct eesoxscsi_info *)host->hostdata;
	unsigned long flags;

	if (len > 1) {
		spin_lock_irqsave(host->host_lock, flags);
		if (buf[0] != '0') {
			info->control |= EESOX_TERM_ENABLE;
		} else {
			info->control &= ~EESOX_TERM_ENABLE;
		}
		writeb(info->control, info->ctl_port);
		spin_unlock_irqrestore(host->host_lock, flags);
	}

	return len;
}