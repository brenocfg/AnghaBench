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
 scalar_t__ rds_ib_sysctl_hdr ; 
 int /*<<< orphan*/  unregister_net_sysctl_table (scalar_t__) ; 

void rds_ib_sysctl_exit(void)
{
	if (rds_ib_sysctl_hdr)
		unregister_net_sysctl_table(rds_ib_sysctl_hdr);
}