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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int posted_request_count; int max_posted_request_count; int pending_request_count; int max_pending_request_count; int sgl_entries; int max_sgl_entries; int sector_count; int max_sector_count; int num_resets; int aen_count; TYPE_1__* host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_2__ TW_Device_Extension ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 char* TW_DRIVER_VERSION ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t tw_show_stats(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct Scsi_Host *host = class_to_shost(dev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;
	unsigned long flags = 0;
	ssize_t len;

	spin_lock_irqsave(tw_dev->host->host_lock, flags);
	len = snprintf(buf, PAGE_SIZE, "3w-xxxx Driver version: %s\n"
		       "Current commands posted:   %4d\n"
		       "Max commands posted:       %4d\n"
		       "Current pending commands:  %4d\n"
		       "Max pending commands:      %4d\n"
		       "Last sgl length:           %4d\n"
		       "Max sgl length:            %4d\n"
		       "Last sector count:         %4d\n"
		       "Max sector count:          %4d\n"
		       "SCSI Host Resets:          %4d\n"
		       "AEN's:                     %4d\n", 
		       TW_DRIVER_VERSION,
		       tw_dev->posted_request_count,
		       tw_dev->max_posted_request_count,
		       tw_dev->pending_request_count,
		       tw_dev->max_pending_request_count,
		       tw_dev->sgl_entries,
		       tw_dev->max_sgl_entries,
		       tw_dev->sector_count,
		       tw_dev->max_sector_count,
		       tw_dev->num_resets,
		       tw_dev->aen_count);
	spin_unlock_irqrestore(tw_dev->host->host_lock, flags);
	return len;
}