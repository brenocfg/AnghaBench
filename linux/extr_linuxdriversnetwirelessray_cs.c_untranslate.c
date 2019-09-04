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
struct snaphdr_t {int dummy; } ;
struct sk_buff {int data; } ;
struct ieee80211_hdr {int dummy; } ;
struct ethhdr {int* h_dest; int* h_source; void* h_proto; } ;
struct TYPE_2__ {int dsap; int ssap; int ctrl; int /*<<< orphan*/  org; scalar_t__ ethertype; } ;
typedef  TYPE_1__ snaphdr_t ;
typedef  int /*<<< orphan*/  ray_dev_t ;
typedef  void* __be16 ;
typedef  int UCHAR ;

/* Variables and functions */
 int ADDRLEN ; 
 int ETH_HLEN ; 
#define  ETH_P_AARP 129 
#define  ETH_P_IPX 128 
 int RX_MAC_HEADER_LENGTH ; 
 void* htons (int) ; 
 int* ieee80211_get_DA (struct ieee80211_hdr*) ; 
 int* ieee80211_get_SA (struct ieee80211_hdr*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int ntohs (void*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void untranslate(ray_dev_t *local, struct sk_buff *skb, int len)
{
	snaphdr_t *psnap = (snaphdr_t *) (skb->data + RX_MAC_HEADER_LENGTH);
	struct ieee80211_hdr *pmac = (struct ieee80211_hdr *)skb->data;
	__be16 type = *(__be16 *) psnap->ethertype;
	int delta;
	struct ethhdr *peth;
	UCHAR srcaddr[ADDRLEN];
	UCHAR destaddr[ADDRLEN];
	static const UCHAR org_bridge[3] = { 0, 0, 0xf8 };
	static const UCHAR org_1042[3] = { 0, 0, 0 };

	memcpy(destaddr, ieee80211_get_DA(pmac), ADDRLEN);
	memcpy(srcaddr, ieee80211_get_SA(pmac), ADDRLEN);

#if 0
	if {
		print_hex_dump(KERN_DEBUG, "skb->data before untranslate: ",
			       DUMP_PREFIX_NONE, 16, 1,
			       skb->data, 64, true);
		printk(KERN_DEBUG
		       "type = %08x, xsap = %02x%02x%02x, org = %02x02x02x\n",
		       ntohs(type), psnap->dsap, psnap->ssap, psnap->ctrl,
		       psnap->org[0], psnap->org[1], psnap->org[2]);
		printk(KERN_DEBUG "untranslate skb->data = %p\n", skb->data);
	}
#endif

	if (psnap->dsap != 0xaa || psnap->ssap != 0xaa || psnap->ctrl != 3) {
		/* not a snap type so leave it alone */
		pr_debug("ray_cs untranslate NOT SNAP %02x %02x %02x\n",
		      psnap->dsap, psnap->ssap, psnap->ctrl);

		delta = RX_MAC_HEADER_LENGTH - ETH_HLEN;
		peth = (struct ethhdr *)(skb->data + delta);
		peth->h_proto = htons(len - RX_MAC_HEADER_LENGTH);
	} else { /* Its a SNAP */
		if (memcmp(psnap->org, org_bridge, 3) == 0) {
		/* EtherII and nuke the LLC */
			pr_debug("ray_cs untranslate Bridge encap\n");
			delta = RX_MAC_HEADER_LENGTH
			    + sizeof(struct snaphdr_t) - ETH_HLEN;
			peth = (struct ethhdr *)(skb->data + delta);
			peth->h_proto = type;
		} else if (memcmp(psnap->org, org_1042, 3) == 0) {
			switch (ntohs(type)) {
			case ETH_P_IPX:
			case ETH_P_AARP:
				pr_debug("ray_cs untranslate RFC IPX/AARP\n");
				delta = RX_MAC_HEADER_LENGTH - ETH_HLEN;
				peth = (struct ethhdr *)(skb->data + delta);
				peth->h_proto =
				    htons(len - RX_MAC_HEADER_LENGTH);
				break;
			default:
				pr_debug("ray_cs untranslate RFC default\n");
				delta = RX_MAC_HEADER_LENGTH +
				    sizeof(struct snaphdr_t) - ETH_HLEN;
				peth = (struct ethhdr *)(skb->data + delta);
				peth->h_proto = type;
				break;
			}
		} else {
			printk("ray_cs untranslate very confused by packet\n");
			delta = RX_MAC_HEADER_LENGTH - ETH_HLEN;
			peth = (struct ethhdr *)(skb->data + delta);
			peth->h_proto = type;
		}
	}
/* TBD reserve  skb_reserve(skb, delta); */
	skb_pull(skb, delta);
	pr_debug("untranslate after skb_pull(%d), skb->data = %p\n", delta,
	      skb->data);
	memcpy(peth->h_dest, destaddr, ADDRLEN);
	memcpy(peth->h_source, srcaddr, ADDRLEN);
#if 0
	{
		int i;
		printk(KERN_DEBUG "skb->data after untranslate:");
		for (i = 0; i < 64; i++)
			printk("%02x ", skb->data[i]);
		printk("\n");
	}
#endif
}