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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct se_node_acl {int dummy; } ;
struct se_dev_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_scsi3_ua_allocate (struct se_dev_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,int /*<<< orphan*/ ) ; 

void target_ua_allocate_lun(struct se_node_acl *nacl,
			    u32 unpacked_lun, u8 asc, u8 ascq)
{
	struct se_dev_entry *deve;

	if (!nacl)
		return;

	rcu_read_lock();
	deve = target_nacl_find_deve(nacl, unpacked_lun);
	if (!deve) {
		rcu_read_unlock();
		return;
	}

	core_scsi3_ua_allocate(deve, asc, ascq);
	rcu_read_unlock();
}