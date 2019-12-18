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
struct wpan_dev {int /*<<< orphan*/  extended_addr; int /*<<< orphan*/  pan_id; int /*<<< orphan*/  ackreq; } ;
struct sk_buff {int mac_len; } ;
struct net_device {TYPE_1__* ieee802154_ptr; } ;
struct ieee802154_sub_if_data {struct wpan_dev wpan_dev; } ;
struct ieee802154_mac_cb {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  extended_addr; void* mode; int /*<<< orphan*/  pan_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  pan_id; int /*<<< orphan*/  extended_addr; void* mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  ack_request; int /*<<< orphan*/  type; } ;
struct ieee802154_hdr {int seq; TYPE_3__ source; TYPE_2__ dest; TYPE_4__ fc; } ;
struct TYPE_5__ {int /*<<< orphan*/  dsn; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 void* IEEE802154_ADDR_LONG ; 
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  IEEE802154_FC_TYPE_DATA ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802154_be64_to_le64 (int /*<<< orphan*/ *,void const*) ; 
 int ieee802154_hdr_push (struct sk_buff*,struct ieee802154_hdr*) ; 
 unsigned int ieee802154_max_payload (struct ieee802154_hdr*) ; 
 scalar_t__ mac802154_set_header_security (struct ieee802154_sub_if_data*,struct ieee802154_hdr*,struct ieee802154_mac_cb*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int mac802154_header_create(struct sk_buff *skb,
				   struct net_device *dev,
				   unsigned short type,
				   const void *daddr,
				   const void *saddr,
				   unsigned len)
{
	struct ieee802154_hdr hdr;
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct wpan_dev *wpan_dev = &sdata->wpan_dev;
	struct ieee802154_mac_cb cb = { };
	int hlen;

	if (!daddr)
		return -EINVAL;

	memset(&hdr.fc, 0, sizeof(hdr.fc));
	hdr.fc.type = IEEE802154_FC_TYPE_DATA;
	hdr.fc.ack_request = wpan_dev->ackreq;
	hdr.seq = atomic_inc_return(&dev->ieee802154_ptr->dsn) & 0xFF;

	/* TODO currently a workaround to give zero cb block to set
	 * security parameters defaults according MIB.
	 */
	if (mac802154_set_header_security(sdata, &hdr, &cb) < 0)
		return -EINVAL;

	hdr.dest.pan_id = wpan_dev->pan_id;
	hdr.dest.mode = IEEE802154_ADDR_LONG;
	ieee802154_be64_to_le64(&hdr.dest.extended_addr, daddr);

	hdr.source.pan_id = hdr.dest.pan_id;
	hdr.source.mode = IEEE802154_ADDR_LONG;

	if (!saddr)
		hdr.source.extended_addr = wpan_dev->extended_addr;
	else
		ieee802154_be64_to_le64(&hdr.source.extended_addr, saddr);

	hlen = ieee802154_hdr_push(skb, &hdr);
	if (hlen < 0)
		return -EINVAL;

	skb_reset_mac_header(skb);
	skb->mac_len = hlen;

	if (len > ieee802154_max_payload(&hdr))
		return -EMSGSIZE;

	return hlen;
}