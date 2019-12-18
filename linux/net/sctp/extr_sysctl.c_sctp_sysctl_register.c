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
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  register_net_sysctl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_sysctl_header ; 
 int /*<<< orphan*/  sctp_table ; 

void sctp_sysctl_register(void)
{
	sctp_sysctl_header = register_net_sysctl(&init_net, "net/sctp", sctp_table);
}