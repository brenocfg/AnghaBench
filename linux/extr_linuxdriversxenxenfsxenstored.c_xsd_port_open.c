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
struct inode {int dummy; } ;
struct file {void* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_store_evtchn ; 

__attribute__((used)) static int xsd_port_open(struct inode *inode, struct file *file)
{
	file->private_data = (void *)kasprintf(GFP_KERNEL, "%d",
					       xen_store_evtchn);
	if (!file->private_data)
		return -ENOMEM;
	return 0;
}