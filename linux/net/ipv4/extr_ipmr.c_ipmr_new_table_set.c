#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mr_tables; } ;
struct net {TYPE_1__ ipv4; } ;
struct mr_table {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmr_new_table_set(struct mr_table *mrt,
			       struct net *net)
{
#ifdef CONFIG_IP_MROUTE_MULTIPLE_TABLES
	list_add_tail_rcu(&mrt->list, &net->ipv4.mr_tables);
#endif
}