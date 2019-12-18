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
typedef  int /*<<< orphan*/  uuid_t ;
struct key {int dummy; } ;
struct afs_vl_cursor {TYPE_1__* server; } ;
struct afs_cell {int dummy; } ;
struct afs_addr_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VLSERVER_FL_IS_YFS ; 
 int ERESTARTSYS ; 
 struct afs_addr_list* ERR_PTR (int) ; 
 scalar_t__ afs_begin_vlserver_operation (struct afs_vl_cursor*,struct afs_cell*,struct key*) ; 
 int afs_end_vlserver_operation (struct afs_vl_cursor*) ; 
 scalar_t__ afs_select_vlserver (struct afs_vl_cursor*) ; 
 struct afs_addr_list* afs_vl_get_addrs_u (struct afs_vl_cursor*,int /*<<< orphan*/  const*) ; 
 struct afs_addr_list* afs_yfsvl_get_endpoints (struct afs_vl_cursor*,int /*<<< orphan*/  const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct afs_addr_list *afs_vl_lookup_addrs(struct afs_cell *cell,
						 struct key *key, const uuid_t *uuid)
{
	struct afs_vl_cursor vc;
	struct afs_addr_list *alist = NULL;
	int ret;

	ret = -ERESTARTSYS;
	if (afs_begin_vlserver_operation(&vc, cell, key)) {
		while (afs_select_vlserver(&vc)) {
			if (test_bit(AFS_VLSERVER_FL_IS_YFS, &vc.server->flags))
				alist = afs_yfsvl_get_endpoints(&vc, uuid);
			else
				alist = afs_vl_get_addrs_u(&vc, uuid);
		}

		ret = afs_end_vlserver_operation(&vc);
	}

	return ret < 0 ? ERR_PTR(ret) : alist;
}