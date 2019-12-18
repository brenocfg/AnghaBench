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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  p9_xen_trans ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  v9fs_register_trans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_unregister_trans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_9pfs_front_driver ; 
 int /*<<< orphan*/  xen_domain () ; 
 int xenbus_register_frontend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p9_trans_xen_init(void)
{
	int rc;

	if (!xen_domain())
		return -ENODEV;

	pr_info("Initialising Xen transport for 9pfs\n");

	v9fs_register_trans(&p9_xen_trans);
	rc = xenbus_register_frontend(&xen_9pfs_front_driver);
	if (rc)
		v9fs_unregister_trans(&p9_xen_trans);

	return rc;
}