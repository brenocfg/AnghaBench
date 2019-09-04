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
struct siox_device {unsigned int status_errors; int /*<<< orphan*/  smaster; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  siox_master_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siox_master_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct siox_device* to_siox_device (struct device*) ; 

__attribute__((used)) static ssize_t status_errors_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct siox_device *sdev = to_siox_device(dev);
	unsigned int status_errors;

	siox_master_lock(sdev->smaster);

	status_errors = sdev->status_errors;

	siox_master_unlock(sdev->smaster);

	return sprintf(buf, "%u\n", status_errors);
}