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
struct ieee802154_hdr_fc {scalar_t__ dest_addr_mode; scalar_t__ source_addr_mode; int intra_pan; int version; scalar_t__ security_enabled; } ;
typedef  struct ieee802154_hdr_fc u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; scalar_t__ pan_id; } ;
struct ieee802154_hdr {int /*<<< orphan*/  sec; TYPE_1__ source; TYPE_1__ dest; struct ieee802154_hdr_fc seq; struct ieee802154_hdr_fc fc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IEEE802154_ADDR_NONE ; 
 int IEEE802154_MAX_HEADER_LEN ; 
 int ieee802154_hdr_push_addr (struct ieee802154_hdr_fc*,TYPE_1__*,int) ; 
 int ieee802154_hdr_push_sechdr (struct ieee802154_hdr_fc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct ieee802154_hdr_fc*,struct ieee802154_hdr_fc*,int) ; 
 struct ieee802154_hdr_fc* skb_push (struct sk_buff*,int) ; 

int
ieee802154_hdr_push(struct sk_buff *skb, struct ieee802154_hdr *hdr)
{
	u8 buf[IEEE802154_MAX_HEADER_LEN];
	int pos = 2;
	int rc;
	struct ieee802154_hdr_fc *fc = &hdr->fc;

	buf[pos++] = hdr->seq;

	fc->dest_addr_mode = hdr->dest.mode;

	rc = ieee802154_hdr_push_addr(buf + pos, &hdr->dest, false);
	if (rc < 0)
		return -EINVAL;
	pos += rc;

	fc->source_addr_mode = hdr->source.mode;

	if (hdr->source.pan_id == hdr->dest.pan_id &&
	    hdr->dest.mode != IEEE802154_ADDR_NONE)
		fc->intra_pan = true;

	rc = ieee802154_hdr_push_addr(buf + pos, &hdr->source, fc->intra_pan);
	if (rc < 0)
		return -EINVAL;
	pos += rc;

	if (fc->security_enabled) {
		fc->version = 1;

		rc = ieee802154_hdr_push_sechdr(buf + pos, &hdr->sec);
		if (rc < 0)
			return -EINVAL;

		pos += rc;
	}

	memcpy(buf, fc, 2);

	memcpy(skb_push(skb, pos), buf, pos);

	return pos;
}