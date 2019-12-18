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
struct netdev_hw_addr_list {int dummy; } ;
struct netdev_hw_addr {int /*<<< orphan*/  refcount; int /*<<< orphan*/  sync_cnt; int /*<<< orphan*/  type; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EEXIST ; 
 int __hw_addr_add_ex (struct netdev_hw_addr_list*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __hw_addr_sync_one(struct netdev_hw_addr_list *to_list,
			       struct netdev_hw_addr *ha,
			       int addr_len)
{
	int err;

	err = __hw_addr_add_ex(to_list, ha->addr, addr_len, ha->type,
			       false, true, ha->sync_cnt);
	if (err && err != -EEXIST)
		return err;

	if (!err) {
		ha->sync_cnt++;
		ha->refcount++;
	}

	return 0;
}