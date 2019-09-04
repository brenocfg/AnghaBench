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
struct t10_wwn {int* vendor; int* model; int* revision; } ;
struct se_device {TYPE_1__* transport; struct t10_wwn t10_wwn; } ;
struct TYPE_2__ {int (* get_device_type ) (struct se_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 char* scsi_device_type (int) ; 
 int stub1 (struct se_device*) ; 

__attribute__((used)) static void scsi_dump_inquiry(struct se_device *dev)
{
	struct t10_wwn *wwn = &dev->t10_wwn;
	char buf[17];
	int i, device_type;
	/*
	 * Print Linux/SCSI style INQUIRY formatting to the kernel ring buffer
	 */
	for (i = 0; i < 8; i++)
		if (wwn->vendor[i] >= 0x20)
			buf[i] = wwn->vendor[i];
		else
			buf[i] = ' ';
	buf[i] = '\0';
	pr_debug("  Vendor: %s\n", buf);

	for (i = 0; i < 16; i++)
		if (wwn->model[i] >= 0x20)
			buf[i] = wwn->model[i];
		else
			buf[i] = ' ';
	buf[i] = '\0';
	pr_debug("  Model: %s\n", buf);

	for (i = 0; i < 4; i++)
		if (wwn->revision[i] >= 0x20)
			buf[i] = wwn->revision[i];
		else
			buf[i] = ' ';
	buf[i] = '\0';
	pr_debug("  Revision: %s\n", buf);

	device_type = dev->transport->get_device_type(dev);
	pr_debug("  Type:   %s ", scsi_device_type(device_type));
}