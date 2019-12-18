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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee802154_llsec_device {int /*<<< orphan*/  list; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  keys; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  pan_id; } ;
struct mac802154_llsec_device {struct ieee802154_llsec_device dev; int /*<<< orphan*/  bucket_hw; int /*<<< orphan*/  bucket_s; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  devices; } ;
struct mac802154_llsec {TYPE_1__ table; int /*<<< orphan*/  devices_hw; int /*<<< orphan*/  devices_short; } ;
typedef  int /*<<< orphan*/  hwkey ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE802154_ADDR_LEN ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mac802154_llsec_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ llsec_dev_find_long (struct mac802154_llsec*,int /*<<< orphan*/ ) ; 
 scalar_t__ llsec_dev_find_short (struct mac802154_llsec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llsec_dev_hash_long (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llsec_dev_hash_short (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ llsec_dev_use_shortaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mac802154_llsec_dev_add(struct mac802154_llsec *sec,
			    const struct ieee802154_llsec_device *dev)
{
	struct mac802154_llsec_device *entry;
	u32 skey = llsec_dev_hash_short(dev->short_addr, dev->pan_id);
	u64 hwkey = llsec_dev_hash_long(dev->hwaddr);

	BUILD_BUG_ON(sizeof(hwkey) != IEEE802154_ADDR_LEN);

	if ((llsec_dev_use_shortaddr(dev->short_addr) &&
	     llsec_dev_find_short(sec, dev->short_addr, dev->pan_id)) ||
	     llsec_dev_find_long(sec, dev->hwaddr))
		return -EEXIST;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	entry->dev = *dev;
	spin_lock_init(&entry->lock);
	INIT_LIST_HEAD(&entry->dev.keys);

	if (llsec_dev_use_shortaddr(dev->short_addr))
		hash_add_rcu(sec->devices_short, &entry->bucket_s, skey);
	else
		INIT_HLIST_NODE(&entry->bucket_s);

	hash_add_rcu(sec->devices_hw, &entry->bucket_hw, hwkey);
	list_add_tail_rcu(&entry->dev.list, &sec->table.devices);

	return 0;
}