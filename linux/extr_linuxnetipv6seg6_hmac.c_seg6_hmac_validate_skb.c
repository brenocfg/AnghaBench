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
typedef  int /*<<< orphan*/  u8 ;
struct sr6_tlv_hmac {int /*<<< orphan*/  hmac; int /*<<< orphan*/  hmackeyid; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct seg6_hmac_info {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_sr_hdr {int dummy; } ;
struct TYPE_3__ {scalar_t__ seg6_require_hmac; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct TYPE_4__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int SEG6_HMAC_FIELD_LEN ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct sr6_tlv_hmac* seg6_get_tlv_hmac (struct ipv6_sr_hdr*) ; 
 scalar_t__ seg6_hmac_compute (struct seg6_hmac_info*,struct ipv6_sr_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct seg6_hmac_info* seg6_hmac_info_lookup (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

bool seg6_hmac_validate_skb(struct sk_buff *skb)
{
	u8 hmac_output[SEG6_HMAC_FIELD_LEN];
	struct net *net = dev_net(skb->dev);
	struct seg6_hmac_info *hinfo;
	struct sr6_tlv_hmac *tlv;
	struct ipv6_sr_hdr *srh;
	struct inet6_dev *idev;

	idev = __in6_dev_get(skb->dev);

	srh = (struct ipv6_sr_hdr *)skb_transport_header(skb);

	tlv = seg6_get_tlv_hmac(srh);

	/* mandatory check but no tlv */
	if (idev->cnf.seg6_require_hmac > 0 && !tlv)
		return false;

	/* no check */
	if (idev->cnf.seg6_require_hmac < 0)
		return true;

	/* check only if present */
	if (idev->cnf.seg6_require_hmac == 0 && !tlv)
		return true;

	/* now, seg6_require_hmac >= 0 && tlv */

	hinfo = seg6_hmac_info_lookup(net, be32_to_cpu(tlv->hmackeyid));
	if (!hinfo)
		return false;

	if (seg6_hmac_compute(hinfo, srh, &ipv6_hdr(skb)->saddr, hmac_output))
		return false;

	if (memcmp(hmac_output, tlv->hmac, SEG6_HMAC_FIELD_LEN) != 0)
		return false;

	return true;
}