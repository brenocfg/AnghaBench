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
typedef  int u32 ;
struct net {int dummy; } ;
struct mr_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mr_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 int RT_TABLE_DEFAULT ; 
 int /*<<< orphan*/  ipmr_expire_process ; 
 struct mr_table* ipmr_get_table (struct net*,int) ; 
 int /*<<< orphan*/  ipmr_mr_table_ops ; 
 int /*<<< orphan*/  ipmr_new_table_set ; 
 struct mr_table* mr_table_alloc (struct net*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mr_table *ipmr_new_table(struct net *net, u32 id)
{
	struct mr_table *mrt;

	/* "pimreg%u" should not exceed 16 bytes (IFNAMSIZ) */
	if (id != RT_TABLE_DEFAULT && id >= 1000000000)
		return ERR_PTR(-EINVAL);

	mrt = ipmr_get_table(net, id);
	if (mrt)
		return mrt;

	return mr_table_alloc(net, id, &ipmr_mr_table_ops,
			      ipmr_expire_process, ipmr_new_table_set);
}