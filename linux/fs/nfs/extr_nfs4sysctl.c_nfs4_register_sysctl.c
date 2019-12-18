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
 int ENOMEM ; 
 int /*<<< orphan*/ * nfs4_callback_sysctl_table ; 
 int /*<<< orphan*/  nfs4_cb_sysctl_root ; 
 int /*<<< orphan*/ * register_sysctl_table (int /*<<< orphan*/ ) ; 

int nfs4_register_sysctl(void)
{
	nfs4_callback_sysctl_table = register_sysctl_table(nfs4_cb_sysctl_root);
	if (nfs4_callback_sysctl_table == NULL)
		return -ENOMEM;
	return 0;
}