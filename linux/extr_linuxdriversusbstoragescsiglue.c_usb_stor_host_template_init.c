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
struct scsi_host_template {char const* name; char const* proc_name; struct module* module; } ;
struct module {int dummy; } ;

/* Variables and functions */
 struct scsi_host_template usb_stor_host_template ; 

void usb_stor_host_template_init(struct scsi_host_template *sht,
				 const char *name, struct module *owner)
{
	*sht = usb_stor_host_template;
	sht->name = name;
	sht->proc_name = name;
	sht->module = owner;
}