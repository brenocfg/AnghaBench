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
typedef  int u8 ;
struct siox_device {int status_read_clean; int /*<<< orphan*/  smaster; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int SIOX_STATUS_WDG ; 
 int /*<<< orphan*/  siox_master_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siox_master_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct siox_device* to_siox_device (struct device*) ; 

__attribute__((used)) static ssize_t watchdog_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct siox_device *sdev = to_siox_device(dev);
	u8 status;

	siox_master_lock(sdev->smaster);

	status = sdev->status_read_clean;

	siox_master_unlock(sdev->smaster);

	return sprintf(buf, "%d\n", status & SIOX_STATUS_WDG);
}