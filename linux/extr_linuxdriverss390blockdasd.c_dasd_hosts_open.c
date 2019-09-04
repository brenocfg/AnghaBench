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
struct inode {struct dasd_device* i_private; } ;
struct file {int dummy; } ;
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_hosts_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct dasd_device*) ; 

__attribute__((used)) static int dasd_hosts_open(struct inode *inode, struct file *file)
{
	struct dasd_device *device = inode->i_private;

	return single_open(file, dasd_hosts_show, device);
}