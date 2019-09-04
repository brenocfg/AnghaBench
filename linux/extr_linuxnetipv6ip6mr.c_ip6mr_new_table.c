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
typedef  int /*<<< orphan*/  u32 ;
struct net {int dummy; } ;
struct mr_table {int dummy; } ;

/* Variables and functions */
 struct mr_table* ip6mr_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6mr_mr_table_ops ; 
 int /*<<< orphan*/  ip6mr_new_table_set ; 
 int /*<<< orphan*/  ipmr_expire_process ; 
 struct mr_table* mr_table_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mr_table *ip6mr_new_table(struct net *net, u32 id)
{
	struct mr_table *mrt;

	mrt = ip6mr_get_table(net, id);
	if (mrt)
		return mrt;

	return mr_table_alloc(net, id, &ip6mr_mr_table_ops,
			      ipmr_expire_process, ip6mr_new_table_set);
}