#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct mac802154_llsec_key {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  seclevel_exempt; } ;
struct mac802154_llsec_device {TYPE_4__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  enabled; } ;
struct mac802154_llsec {int /*<<< orphan*/  lock; TYPE_1__ params; } ;
struct ieee802154_llsec_seclevel {int sec_levels; scalar_t__ device_override; } ;
struct ieee802154_llsec_key_id {int dummy; } ;
struct TYPE_7__ {scalar_t__ level; int /*<<< orphan*/  frame_counter; } ;
struct TYPE_6__ {scalar_t__ version; int /*<<< orphan*/  type; int /*<<< orphan*/  security_enabled; } ;
struct ieee802154_hdr {TYPE_3__ sec; TYPE_2__ fc; int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EINVAL ; 
 int ENOKEY ; 
 int EOVERFLOW ; 
 scalar_t__ ieee802154_hdr_peek (struct sk_buff*,struct ieee802154_hdr*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int llsec_do_decrypt (struct sk_buff*,struct mac802154_llsec*,struct ieee802154_hdr*,struct mac802154_llsec_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llsec_key_put (struct mac802154_llsec_key*) ; 
 struct mac802154_llsec_device* llsec_lookup_dev (struct mac802154_llsec*,int /*<<< orphan*/ *) ; 
 struct mac802154_llsec_key* llsec_lookup_key (struct mac802154_llsec*,struct ieee802154_hdr*,int /*<<< orphan*/ *,struct ieee802154_llsec_key_id*) ; 
 scalar_t__ llsec_lookup_seclevel (struct mac802154_llsec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee802154_llsec_seclevel*) ; 
 int llsec_update_devkey_info (struct mac802154_llsec_device*,struct ieee802154_llsec_key_id*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

int mac802154_llsec_decrypt(struct mac802154_llsec *sec, struct sk_buff *skb)
{
	struct ieee802154_hdr hdr;
	struct mac802154_llsec_key *key;
	struct ieee802154_llsec_key_id key_id;
	struct mac802154_llsec_device *dev;
	struct ieee802154_llsec_seclevel seclevel;
	int err;
	__le64 dev_addr;
	u32 frame_ctr;

	if (ieee802154_hdr_peek(skb, &hdr) < 0)
		return -EINVAL;
	if (!hdr.fc.security_enabled)
		return 0;
	if (hdr.fc.version == 0)
		return -EINVAL;

	read_lock_bh(&sec->lock);
	if (!sec->params.enabled) {
		read_unlock_bh(&sec->lock);
		return -EINVAL;
	}
	read_unlock_bh(&sec->lock);

	rcu_read_lock();

	key = llsec_lookup_key(sec, &hdr, &hdr.source, &key_id);
	if (!key) {
		err = -ENOKEY;
		goto fail;
	}

	dev = llsec_lookup_dev(sec, &hdr.source);
	if (!dev) {
		err = -EINVAL;
		goto fail_dev;
	}

	if (llsec_lookup_seclevel(sec, hdr.fc.type, 0, &seclevel) < 0) {
		err = -EINVAL;
		goto fail_dev;
	}

	if (!(seclevel.sec_levels & BIT(hdr.sec.level)) &&
	    (hdr.sec.level == 0 && seclevel.device_override &&
	     !dev->dev.seclevel_exempt)) {
		err = -EINVAL;
		goto fail_dev;
	}

	frame_ctr = le32_to_cpu(hdr.sec.frame_counter);

	if (frame_ctr == 0xffffffff) {
		err = -EOVERFLOW;
		goto fail_dev;
	}

	err = llsec_update_devkey_info(dev, &key_id, frame_ctr);
	if (err)
		goto fail_dev;

	dev_addr = dev->dev.hwaddr;

	rcu_read_unlock();

	err = llsec_do_decrypt(skb, sec, &hdr, key, dev_addr);
	llsec_key_put(key);
	return err;

fail_dev:
	llsec_key_put(key);
fail:
	rcu_read_unlock();
	return err;
}