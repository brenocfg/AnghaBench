#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee802154_llsec_key_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; struct ieee802154_llsec_key_id key_id; } ;
struct mac802154_llsec_device_key {TYPE_2__ devkey; } ;
struct TYPE_3__ {int /*<<< orphan*/  keys; } ;
struct mac802154_llsec_device {int /*<<< orphan*/  lock; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct mac802154_llsec_device_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct mac802154_llsec_device_key*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mac802154_llsec_device_key* llsec_devkey_find (struct mac802154_llsec_device*,struct ieee802154_llsec_key_id const*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
llsec_update_devkey_record(struct mac802154_llsec_device *dev,
			   const struct ieee802154_llsec_key_id *in_key)
{
	struct mac802154_llsec_device_key *devkey;

	devkey = llsec_devkey_find(dev, in_key);

	if (!devkey) {
		struct mac802154_llsec_device_key *next;

		next = kzalloc(sizeof(*devkey), GFP_ATOMIC);
		if (!next)
			return -ENOMEM;

		next->devkey.key_id = *in_key;

		spin_lock_bh(&dev->lock);

		devkey = llsec_devkey_find(dev, in_key);
		if (!devkey)
			list_add_rcu(&next->devkey.list, &dev->dev.keys);
		else
			kzfree(next);

		spin_unlock_bh(&dev->lock);
	}

	return 0;
}