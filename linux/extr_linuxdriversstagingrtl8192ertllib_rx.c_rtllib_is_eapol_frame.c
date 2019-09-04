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
typedef  int u8 ;
typedef  int u16 ;
struct sk_buff {int len; int* data; } ;
struct rtllib_hdr_4addr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_ctl; } ;
struct rtllib_device {struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int ETH_P_PAE ; 
 int RTLLIB_FCTL_FROMDS ; 
 int RTLLIB_FCTL_TODS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtllib_is_eapol_frame(struct rtllib_device *ieee,
				    struct sk_buff *skb, size_t hdrlen)
{
	struct net_device *dev = ieee->dev;
	u16 fc, ethertype;
	struct rtllib_hdr_4addr *hdr;
	u8 *pos;

	if (skb->len < 24)
		return 0;

	hdr = (struct rtllib_hdr_4addr *) skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);

	/* check that the frame is unicast frame to us */
	if ((fc & (RTLLIB_FCTL_TODS | RTLLIB_FCTL_FROMDS)) ==
	    RTLLIB_FCTL_TODS &&
	    memcmp(hdr->addr1, dev->dev_addr, ETH_ALEN) == 0 &&
	    memcmp(hdr->addr3, dev->dev_addr, ETH_ALEN) == 0) {
		/* ToDS frame with own addr BSSID and DA */
	} else if ((fc & (RTLLIB_FCTL_TODS | RTLLIB_FCTL_FROMDS)) ==
		   RTLLIB_FCTL_FROMDS &&
		   memcmp(hdr->addr1, dev->dev_addr, ETH_ALEN) == 0) {
		/* FromDS frame with own addr as DA */
	} else
		return 0;

	if (skb->len < 24 + 8)
		return 0;

	/* check for port access entity Ethernet type */
	pos = skb->data + hdrlen;
	ethertype = (pos[6] << 8) | pos[7];
	if (ethertype == ETH_P_PAE)
		return 1;

	return 0;
}