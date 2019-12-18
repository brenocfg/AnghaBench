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
struct wpan_dev {scalar_t__ short_addr; scalar_t__ pan_id; int /*<<< orphan*/  extended_addr; } ;
struct sk_buff {int mac_len; } ;
struct net_device {TYPE_1__* ieee802154_ptr; } ;
struct ieee802154_sub_if_data {struct wpan_dev wpan_dev; } ;
struct ieee802154_mac_cb {int /*<<< orphan*/  ackreq; int /*<<< orphan*/  secen; int /*<<< orphan*/  type; } ;
struct ieee802154_addr {scalar_t__ short_addr; scalar_t__ pan_id; int /*<<< orphan*/  mode; int /*<<< orphan*/  extended_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  ack_request; int /*<<< orphan*/  security_enabled; int /*<<< orphan*/  type; } ;
struct ieee802154_hdr {int seq; struct ieee802154_addr dest; struct ieee802154_addr source; TYPE_2__ fc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dsn; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  IEEE802154_ADDR_BROADCAST ; 
 int /*<<< orphan*/  IEEE802154_ADDR_LONG ; 
 int /*<<< orphan*/  IEEE802154_ADDR_SHORT ; 
 int /*<<< orphan*/  IEEE802154_ADDR_UNDEF ; 
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  IEEE802154_PANID_BROADCAST ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ieee802154_hdr_push (struct sk_buff*,struct ieee802154_hdr*) ; 
 unsigned int ieee802154_max_payload (struct ieee802154_hdr*) ; 
 scalar_t__ mac802154_set_header_security (struct ieee802154_sub_if_data*,struct ieee802154_hdr*,struct ieee802154_mac_cb*) ; 
 struct ieee802154_mac_cb* mac_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int ieee802154_header_create(struct sk_buff *skb,
				    struct net_device *dev,
				    const struct ieee802154_addr *daddr,
				    const struct ieee802154_addr *saddr,
				    unsigned len)
{
	struct ieee802154_hdr hdr;
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct wpan_dev *wpan_dev = &sdata->wpan_dev;
	struct ieee802154_mac_cb *cb = mac_cb(skb);
	int hlen;

	if (!daddr)
		return -EINVAL;

	memset(&hdr.fc, 0, sizeof(hdr.fc));
	hdr.fc.type = cb->type;
	hdr.fc.security_enabled = cb->secen;
	hdr.fc.ack_request = cb->ackreq;
	hdr.seq = atomic_inc_return(&dev->ieee802154_ptr->dsn) & 0xFF;

	if (mac802154_set_header_security(sdata, &hdr, cb) < 0)
		return -EINVAL;

	if (!saddr) {
		if (wpan_dev->short_addr == cpu_to_le16(IEEE802154_ADDR_BROADCAST) ||
		    wpan_dev->short_addr == cpu_to_le16(IEEE802154_ADDR_UNDEF) ||
		    wpan_dev->pan_id == cpu_to_le16(IEEE802154_PANID_BROADCAST)) {
			hdr.source.mode = IEEE802154_ADDR_LONG;
			hdr.source.extended_addr = wpan_dev->extended_addr;
		} else {
			hdr.source.mode = IEEE802154_ADDR_SHORT;
			hdr.source.short_addr = wpan_dev->short_addr;
		}

		hdr.source.pan_id = wpan_dev->pan_id;
	} else {
		hdr.source = *(const struct ieee802154_addr *)saddr;
	}

	hdr.dest = *(const struct ieee802154_addr *)daddr;

	hlen = ieee802154_hdr_push(skb, &hdr);
	if (hlen < 0)
		return -EINVAL;

	skb_reset_mac_header(skb);
	skb->mac_len = hlen;

	if (len > ieee802154_max_payload(&hdr))
		return -EMSGSIZE;

	return hlen;
}