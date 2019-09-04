#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* sysctl_header; } ;
struct net {TYPE_1__ sctp; } ;
struct ctl_table {int dummy; } ;
struct TYPE_4__ {struct ctl_table* ctl_table_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ctl_table*) ; 
 int /*<<< orphan*/  unregister_net_sysctl_table (TYPE_2__*) ; 

void sctp_sysctl_net_unregister(struct net *net)
{
	struct ctl_table *table;

	table = net->sctp.sysctl_header->ctl_table_arg;
	unregister_net_sysctl_table(net->sctp.sysctl_header);
	kfree(table);
}