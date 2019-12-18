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
struct net_device {scalar_t__ type; } ;
struct ieee802154_sub_if_data {int /*<<< orphan*/  sec_mtx; int /*<<< orphan*/  sec; } ;
struct ieee802154_llsec_key_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE802154 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int mac802154_llsec_key_del (int /*<<< orphan*/ *,struct ieee802154_llsec_key_id const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mac802154_del_key(struct net_device *dev,
		      const struct ieee802154_llsec_key_id *id)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	int res;

	BUG_ON(dev->type != ARPHRD_IEEE802154);

	mutex_lock(&sdata->sec_mtx);
	res = mac802154_llsec_key_del(&sdata->sec, id);
	mutex_unlock(&sdata->sec_mtx);

	return res;
}