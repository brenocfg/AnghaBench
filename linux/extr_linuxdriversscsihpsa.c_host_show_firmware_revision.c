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
struct ctlr_info {unsigned char* hba_inquiry_data; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct ctlr_info* shost_to_hba (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static ssize_t host_show_firmware_revision(struct device *dev,
	     struct device_attribute *attr, char *buf)
{
	struct ctlr_info *h;
	struct Scsi_Host *shost = class_to_shost(dev);
	unsigned char *fwrev;

	h = shost_to_hba(shost);
	if (!h->hba_inquiry_data)
		return 0;
	fwrev = &h->hba_inquiry_data[32];
	return snprintf(buf, 20, "%c%c%c%c\n",
		fwrev[0], fwrev[1], fwrev[2], fwrev[3]);
}