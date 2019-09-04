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
 int /*<<< orphan*/  p9_xen_trans ; 
 int /*<<< orphan*/  v9fs_unregister_trans (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_9pfs_front_driver ; 
 void xenbus_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void p9_trans_xen_exit(void)
{
	v9fs_unregister_trans(&p9_xen_trans);
	return xenbus_unregister_driver(&xen_9pfs_front_driver);
}