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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct mac802154_llsec_device {int /*<<< orphan*/  rcu; TYPE_1__ dev; int /*<<< orphan*/  bucket_hw; int /*<<< orphan*/  bucket_s; } ;
struct mac802154_llsec {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct mac802154_llsec_device* llsec_dev_find_long (struct mac802154_llsec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llsec_dev_free_rcu ; 

int mac802154_llsec_dev_del(struct mac802154_llsec *sec, __le64 device_addr)
{
	struct mac802154_llsec_device *pos;

	pos = llsec_dev_find_long(sec, device_addr);
	if (!pos)
		return -ENOENT;

	hash_del_rcu(&pos->bucket_s);
	hash_del_rcu(&pos->bucket_hw);
	list_del_rcu(&pos->dev.list);
	call_rcu(&pos->rcu, llsec_dev_free_rcu);

	return 0;
}