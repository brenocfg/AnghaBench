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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int eh_deadline; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HZ ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static ssize_t
show_shost_eh_deadline(struct device *dev,
		      struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);

	if (shost->eh_deadline == -1)
		return snprintf(buf, strlen("off") + 2, "off\n");
	return sprintf(buf, "%u\n", shost->eh_deadline / HZ);
}