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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int len; struct net_device* dev; void* protocol; scalar_t__* data; } ;
struct TYPE_6__ {int fecn; int becn; } ;
struct pvc_device {TYPE_2__ state; struct net_device* ether; struct net_device* main; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_compressed; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;
struct fr_hdr {int fecn; int becn; scalar_t__ ea1; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_5__ {scalar_t__ lmi; } ;
struct TYPE_8__ {TYPE_1__ settings; } ;

/* Variables and functions */
#define  ETH_P_ARP 131 
#define  ETH_P_IP 130 
#define  ETH_P_IPV6 129 
#define  ETH_P_IPX 128 
 scalar_t__ FR_PAD ; 
 scalar_t__ FR_UI ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ LMI_ANSI ; 
 scalar_t__ LMI_CCITT ; 
 scalar_t__ LMI_CCITT_ANSI_DLCI ; 
 scalar_t__ LMI_CISCO ; 
 scalar_t__ LMI_CISCO_DLCI ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 scalar_t__ NLPID_IP ; 
 scalar_t__ NLPID_IPV6 ; 
 scalar_t__ NLPID_SNAP ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 void* eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct pvc_device* find_pvc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fr_lmi_recv (struct net_device*,struct sk_buff*) ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ q922_to_dlci (scalar_t__*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_4__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fr_rx(struct sk_buff *skb)
{
	struct net_device *frad = skb->dev;
	hdlc_device *hdlc = dev_to_hdlc(frad);
	struct fr_hdr *fh = (struct fr_hdr *)skb->data;
	u8 *data = skb->data;
	u16 dlci;
	struct pvc_device *pvc;
	struct net_device *dev = NULL;

	if (skb->len <= 4 || fh->ea1 || data[2] != FR_UI)
		goto rx_error;

	dlci = q922_to_dlci(skb->data);

	if ((dlci == LMI_CCITT_ANSI_DLCI &&
	     (state(hdlc)->settings.lmi == LMI_ANSI ||
	      state(hdlc)->settings.lmi == LMI_CCITT)) ||
	    (dlci == LMI_CISCO_DLCI &&
	     state(hdlc)->settings.lmi == LMI_CISCO)) {
		if (fr_lmi_recv(frad, skb))
			goto rx_error;
		dev_kfree_skb_any(skb);
		return NET_RX_SUCCESS;
	}

	pvc = find_pvc(hdlc, dlci);
	if (!pvc) {
#ifdef DEBUG_PKT
		netdev_info(frad, "No PVC for received frame's DLCI %d\n",
			    dlci);
#endif
		dev_kfree_skb_any(skb);
		return NET_RX_DROP;
	}

	if (pvc->state.fecn != fh->fecn) {
#ifdef DEBUG_ECN
		printk(KERN_DEBUG "%s: DLCI %d FECN O%s\n", frad->name,
		       dlci, fh->fecn ? "N" : "FF");
#endif
		pvc->state.fecn ^= 1;
	}

	if (pvc->state.becn != fh->becn) {
#ifdef DEBUG_ECN
		printk(KERN_DEBUG "%s: DLCI %d BECN O%s\n", frad->name,
		       dlci, fh->becn ? "N" : "FF");
#endif
		pvc->state.becn ^= 1;
	}


	if ((skb = skb_share_check(skb, GFP_ATOMIC)) == NULL) {
		frad->stats.rx_dropped++;
		return NET_RX_DROP;
	}

	if (data[3] == NLPID_IP) {
		skb_pull(skb, 4); /* Remove 4-byte header (hdr, UI, NLPID) */
		dev = pvc->main;
		skb->protocol = htons(ETH_P_IP);

	} else if (data[3] == NLPID_IPV6) {
		skb_pull(skb, 4); /* Remove 4-byte header (hdr, UI, NLPID) */
		dev = pvc->main;
		skb->protocol = htons(ETH_P_IPV6);

	} else if (skb->len > 10 && data[3] == FR_PAD &&
		   data[4] == NLPID_SNAP && data[5] == FR_PAD) {
		u16 oui = ntohs(*(__be16*)(data + 6));
		u16 pid = ntohs(*(__be16*)(data + 8));
		skb_pull(skb, 10);

		switch ((((u32)oui) << 16) | pid) {
		case ETH_P_ARP: /* routed frame with SNAP */
		case ETH_P_IPX:
		case ETH_P_IP:	/* a long variant */
		case ETH_P_IPV6:
			dev = pvc->main;
			skb->protocol = htons(pid);
			break;

		case 0x80C20007: /* bridged Ethernet frame */
			if ((dev = pvc->ether) != NULL)
				skb->protocol = eth_type_trans(skb, dev);
			break;

		default:
			netdev_info(frad, "Unsupported protocol, OUI=%x PID=%x\n",
				    oui, pid);
			dev_kfree_skb_any(skb);
			return NET_RX_DROP;
		}
	} else {
		netdev_info(frad, "Unsupported protocol, NLPID=%x length=%i\n",
			    data[3], skb->len);
		dev_kfree_skb_any(skb);
		return NET_RX_DROP;
	}

	if (dev) {
		dev->stats.rx_packets++; /* PVC traffic */
		dev->stats.rx_bytes += skb->len;
		if (pvc->state.becn)
			dev->stats.rx_compressed++;
		skb->dev = dev;
		netif_rx(skb);
		return NET_RX_SUCCESS;
	} else {
		dev_kfree_skb_any(skb);
		return NET_RX_DROP;
	}

 rx_error:
	frad->stats.rx_errors++; /* Mark error */
	dev_kfree_skb_any(skb);
	return NET_RX_DROP;
}