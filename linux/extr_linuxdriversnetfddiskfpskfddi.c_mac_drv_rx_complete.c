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
typedef  int u_int ;
struct sk_buff {unsigned char* data; int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {struct sk_buff* skb; } ;
struct s_smt_fp_rxd {TYPE_1__ rxd_os; } ;
struct TYPE_6__ {int rx_bytes; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_7__ {TYPE_2__ gen; } ;
struct TYPE_8__ {TYPE_3__ MacStat; int /*<<< orphan*/  dev; } ;
struct s_smc {TYPE_4__ os; } ;
typedef  TYPE_4__ skfddi_priv ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int FDDI_MAC_HDR_LEN ; 
 unsigned short FDDI_RCF_LEN_MASK ; 
 unsigned char FDDI_RII ; 
 int /*<<< orphan*/  HWM_RX_CHECK (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_LOW_WATERMARK ; 
 int /*<<< orphan*/  dump_data (unsigned char*,int) ; 
 int /*<<< orphan*/  fddi_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_drv_requeue_rxd (struct s_smc*,struct s_smt_fp_rxd volatile*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

void mac_drv_rx_complete(struct s_smc *smc, volatile struct s_smt_fp_rxd *rxd,
			 int frag_count, int len)
{
	skfddi_priv *bp = &smc->os;
	struct sk_buff *skb;
	unsigned char *virt, *cp;
	unsigned short ri;
	u_int RifLength;

	pr_debug("entering mac_drv_rx_complete (len=%d)\n", len);
	if (frag_count != 1) {	// This is not allowed to happen.

		printk("fddi: Multi-fragment receive!\n");
		goto RequeueRxd;	// Re-use the given RXD(s).

	}
	skb = rxd->rxd_os.skb;
	if (!skb) {
		pr_debug("No skb in rxd\n");
		smc->os.MacStat.gen.rx_errors++;
		goto RequeueRxd;
	}
	virt = skb->data;

	// The DMA mapping was released in dma_complete above.

	dump_data(skb->data, len);

	/*
	 * FDDI Frame format:
	 * +-------+-------+-------+------------+--------+------------+
	 * | FC[1] | DA[6] | SA[6] | RIF[0..18] | LLC[3] | Data[0..n] |
	 * +-------+-------+-------+------------+--------+------------+
	 *
	 * FC = Frame Control
	 * DA = Destination Address
	 * SA = Source Address
	 * RIF = Routing Information Field
	 * LLC = Logical Link Control
	 */

	// Remove Routing Information Field (RIF), if present.

	if ((virt[1 + 6] & FDDI_RII) == 0)
		RifLength = 0;
	else {
		int n;
// goos: RIF removal has still to be tested
		pr_debug("RIF found\n");
		// Get RIF length from Routing Control (RC) field.
		cp = virt + FDDI_MAC_HDR_LEN;	// Point behind MAC header.

		ri = ntohs(*((__be16 *) cp));
		RifLength = ri & FDDI_RCF_LEN_MASK;
		if (len < (int) (FDDI_MAC_HDR_LEN + RifLength)) {
			printk("fddi: Invalid RIF.\n");
			goto RequeueRxd;	// Discard the frame.

		}
		virt[1 + 6] &= ~FDDI_RII;	// Clear RII bit.
		// regions overlap

		virt = cp + RifLength;
		for (n = FDDI_MAC_HDR_LEN; n; n--)
			*--virt = *--cp;
		// adjust sbd->data pointer
		skb_pull(skb, RifLength);
		len -= RifLength;
		RifLength = 0;
	}

	// Count statistics.
	smc->os.MacStat.gen.rx_packets++;	// Count indicated receive
						// packets.
	smc->os.MacStat.gen.rx_bytes+=len;	// Count bytes.

	// virt points to header again
	if (virt[1] & 0x01) {	// Check group (multicast) bit.

		smc->os.MacStat.gen.multicast++;
	}

	// deliver frame to system
	rxd->rxd_os.skb = NULL;
	skb_trim(skb, len);
	skb->protocol = fddi_type_trans(skb, bp->dev);

	netif_rx(skb);

	HWM_RX_CHECK(smc, RX_LOW_WATERMARK);
	return;

      RequeueRxd:
	pr_debug("Rx: re-queue RXD.\n");
	mac_drv_requeue_rxd(smc, rxd, frag_count);
	smc->os.MacStat.gen.rx_errors++;	// Count receive packets
						// not indicated.

}