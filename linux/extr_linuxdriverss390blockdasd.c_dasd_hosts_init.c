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
typedef  int umode_t ;
struct dentry {int dummy; } ;
struct dasd_device {struct dentry* hosts_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  dasd_hosts_fops ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct dasd_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_hosts_init(struct dentry *base_dentry,
			    struct dasd_device *device)
{
	struct dentry *pde;
	umode_t mode;

	if (!base_dentry)
		return;

	mode = S_IRUSR | S_IFREG;
	pde = debugfs_create_file("host_access_list", mode, base_dentry,
				  device, &dasd_hosts_fops);
	if (pde && !IS_ERR(pde))
		device->hosts_dentry = pde;
}