#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ctl_table_header {struct ctl_table* ctl_table_arg; } ;
struct ctl_table {int dummy; } ;
struct TYPE_3__ {struct ctl_table_header* sysheader; } ;
typedef  TYPE_1__ ax25_dev ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ctl_table*) ; 
 int /*<<< orphan*/  unregister_net_sysctl_table (struct ctl_table_header*) ; 

void ax25_unregister_dev_sysctl(ax25_dev *ax25_dev)
{
	struct ctl_table_header *header = ax25_dev->sysheader;
	struct ctl_table *table;

	if (header) {
		ax25_dev->sysheader = NULL;
		table = header->ctl_table_arg;
		unregister_net_sysctl_table(header);
		kfree(table);
	}
}