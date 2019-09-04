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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; TYPE_1__* dev; } ;
struct ifeheadr {void* tlv_data; int /*<<< orphan*/  metalen; } ;
struct ethhdr {int dummy; } ;
struct TYPE_2__ {int hard_header_len; } ;

/* Variables and functions */
 int IFE_METAHDRLEN ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct ethhdr*,int) ; 
 int skb_cow_head (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void *ife_encode(struct sk_buff *skb, u16 metalen)
{
	/* OUTERHDR:TOTMETALEN:{TLVHDR:Metadatum:TLVHDR..}:ORIGDATA
	 * where ORIGDATA = original ethernet header ...
	 */
	int hdrm = metalen + IFE_METAHDRLEN;
	int total_push = hdrm + skb->dev->hard_header_len;
	struct ifeheadr *ifehdr;
	struct ethhdr *iethh;	/* inner ether header */
	int skboff = 0;
	int err;

	err = skb_cow_head(skb, total_push);
	if (unlikely(err))
		return NULL;

	iethh = (struct ethhdr *) skb->data;

	__skb_push(skb, total_push);
	memcpy(skb->data, iethh, skb->dev->hard_header_len);
	skb_reset_mac_header(skb);
	skboff += skb->dev->hard_header_len;

	/* total metadata length */
	ifehdr = (struct ifeheadr *) (skb->data + skboff);
	metalen += IFE_METAHDRLEN;
	ifehdr->metalen = htons(metalen);

	return ifehdr->tlv_data;
}