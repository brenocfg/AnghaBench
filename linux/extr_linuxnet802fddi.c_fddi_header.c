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
struct sk_buff {int dummy; } ;
struct net_device {void const* dev_addr; int /*<<< orphan*/  addr_len; } ;
struct TYPE_3__ {int* oui; int /*<<< orphan*/  ethertype; int /*<<< orphan*/  ctrl; void* ssap; void* dsap; } ;
struct TYPE_4__ {TYPE_1__ llc_snap; } ;
struct fddihdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; TYPE_2__ hdr; int /*<<< orphan*/  fc; } ;

/* Variables and functions */
 unsigned short ETH_P_ARP ; 
 unsigned short ETH_P_IP ; 
 unsigned short ETH_P_IPV6 ; 
 void* FDDI_EXTENDED_SAP ; 
 int /*<<< orphan*/  FDDI_FC_K_ASYNC_LLC_DEF ; 
 int FDDI_K_8022_HLEN ; 
 int FDDI_K_SNAP_HLEN ; 
 int /*<<< orphan*/  FDDI_UI_CMD ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 struct fddihdr* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int fddi_header(struct sk_buff *skb, struct net_device *dev,
		       unsigned short type,
		       const void *daddr, const void *saddr, unsigned int len)
{
	int hl = FDDI_K_SNAP_HLEN;
	struct fddihdr *fddi;

	if(type != ETH_P_IP && type != ETH_P_IPV6 && type != ETH_P_ARP)
		hl=FDDI_K_8022_HLEN-3;
	fddi = skb_push(skb, hl);
	fddi->fc			 = FDDI_FC_K_ASYNC_LLC_DEF;
	if(type == ETH_P_IP || type == ETH_P_IPV6 || type == ETH_P_ARP)
	{
		fddi->hdr.llc_snap.dsap		 = FDDI_EXTENDED_SAP;
		fddi->hdr.llc_snap.ssap		 = FDDI_EXTENDED_SAP;
		fddi->hdr.llc_snap.ctrl		 = FDDI_UI_CMD;
		fddi->hdr.llc_snap.oui[0]	 = 0x00;
		fddi->hdr.llc_snap.oui[1]	 = 0x00;
		fddi->hdr.llc_snap.oui[2]	 = 0x00;
		fddi->hdr.llc_snap.ethertype	 = htons(type);
	}

	/* Set the source and destination hardware addresses */

	if (saddr != NULL)
		memcpy(fddi->saddr, saddr, dev->addr_len);
	else
		memcpy(fddi->saddr, dev->dev_addr, dev->addr_len);

	if (daddr != NULL)
	{
		memcpy(fddi->daddr, daddr, dev->addr_len);
		return hl;
	}

	return -hl;
}