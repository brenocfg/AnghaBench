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
struct ieee802154_llsec_device_key {int /*<<< orphan*/  list; int /*<<< orphan*/  key_id; } ;
struct mac802154_llsec_device_key {struct ieee802154_llsec_device_key devkey; } ;
struct TYPE_2__ {int /*<<< orphan*/  keys; } ;
struct mac802154_llsec_device {TYPE_1__ dev; } ;
struct mac802154_llsec {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mac802154_llsec_device_key* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mac802154_llsec_device* llsec_dev_find_long (struct mac802154_llsec*,int /*<<< orphan*/ ) ; 
 scalar_t__ llsec_devkey_find (struct mac802154_llsec_device*,int /*<<< orphan*/ *) ; 

int mac802154_llsec_devkey_add(struct mac802154_llsec *sec,
			       __le64 dev_addr,
			       const struct ieee802154_llsec_device_key *key)
{
	struct mac802154_llsec_device *dev;
	struct mac802154_llsec_device_key *devkey;

	dev = llsec_dev_find_long(sec, dev_addr);

	if (!dev)
		return -ENOENT;

	if (llsec_devkey_find(dev, &key->key_id))
		return -EEXIST;

	devkey = kmalloc(sizeof(*devkey), GFP_KERNEL);
	if (!devkey)
		return -ENOMEM;

	devkey->devkey = *key;
	list_add_tail_rcu(&devkey->devkey.list, &dev->dev.keys);
	return 0;
}