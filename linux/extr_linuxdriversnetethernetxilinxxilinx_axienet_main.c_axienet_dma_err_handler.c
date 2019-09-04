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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct axienet_local {int options; size_t rx_bd_p; size_t tx_bd_p; scalar_t__ rx_bd_ci; scalar_t__ tx_bd_tail; scalar_t__ tx_bd_ci; struct axidma_bd* rx_bd_v; struct axidma_bd* tx_bd_v; struct net_device* ndev; } ;
struct axidma_bd {int cntrl; scalar_t__ app4; scalar_t__ app3; scalar_t__ app2; scalar_t__ app1; scalar_t__ app0; scalar_t__ status; scalar_t__ sw_id_offset; scalar_t__ phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t RX_BD_NUM ; 
 size_t TX_BD_NUM ; 
 size_t XAE_FCC_FCRX_MASK ; 
 int /*<<< orphan*/  XAE_FCC_OFFSET ; 
 size_t XAE_INT_RXRJECT_MASK ; 
 int /*<<< orphan*/  XAE_IP_OFFSET ; 
 int /*<<< orphan*/  XAE_IS_OFFSET ; 
 int XAE_MDIO_MC_MDIOEN_MASK ; 
 int /*<<< orphan*/  XAE_MDIO_MC_OFFSET ; 
 int XAE_OPTION_RXEN ; 
 int XAE_OPTION_TXEN ; 
 int /*<<< orphan*/  XAE_RCW1_OFFSET ; 
 size_t XAE_RCW1_RX_MASK ; 
 int XAXIDMA_BD_CTRL_LENGTH_MASK ; 
 size_t XAXIDMA_COALESCE_MASK ; 
 size_t XAXIDMA_COALESCE_SHIFT ; 
 size_t XAXIDMA_CR_RUNSTOP_MASK ; 
 size_t XAXIDMA_DELAY_MASK ; 
 size_t XAXIDMA_DELAY_SHIFT ; 
 size_t XAXIDMA_DFT_RX_THRESHOLD ; 
 size_t XAXIDMA_DFT_RX_WAITBOUND ; 
 size_t XAXIDMA_DFT_TX_THRESHOLD ; 
 size_t XAXIDMA_DFT_TX_WAITBOUND ; 
 size_t XAXIDMA_IRQ_ALL_MASK ; 
 int /*<<< orphan*/  XAXIDMA_RX_CDESC_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_RX_CR_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_RX_TDESC_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_TX_CDESC_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_TX_CR_OFFSET ; 
 int /*<<< orphan*/  __axienet_device_reset (struct axienet_local*,int /*<<< orphan*/ ) ; 
 size_t axienet_dma_in32 (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_dma_out32 (struct axienet_local*,int /*<<< orphan*/ ,size_t) ; 
 void* axienet_ior (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axienet_iow (struct axienet_local*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  axienet_mdio_wait_until_ready (struct axienet_local*) ; 
 int /*<<< orphan*/  axienet_set_mac_address (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  axienet_set_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  axienet_setoptions (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axienet_dma_err_handler(unsigned long data)
{
	u32 axienet_status;
	u32 cr, i;
	int mdio_mcreg;
	struct axienet_local *lp = (struct axienet_local *) data;
	struct net_device *ndev = lp->ndev;
	struct axidma_bd *cur_p;

	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));
	mdio_mcreg = axienet_ior(lp, XAE_MDIO_MC_OFFSET);
	axienet_mdio_wait_until_ready(lp);
	/* Disable the MDIO interface till Axi Ethernet Reset is completed.
	 * When we do an Axi Ethernet reset, it resets the complete core
	 * including the MDIO. So if MDIO is not disabled when the reset
	 * process is started, MDIO will be broken afterwards.
	 */
	axienet_iow(lp, XAE_MDIO_MC_OFFSET, (mdio_mcreg &
		    ~XAE_MDIO_MC_MDIOEN_MASK));

	__axienet_device_reset(lp, XAXIDMA_TX_CR_OFFSET);
	__axienet_device_reset(lp, XAXIDMA_RX_CR_OFFSET);

	axienet_iow(lp, XAE_MDIO_MC_OFFSET, mdio_mcreg);
	axienet_mdio_wait_until_ready(lp);

	for (i = 0; i < TX_BD_NUM; i++) {
		cur_p = &lp->tx_bd_v[i];
		if (cur_p->phys)
			dma_unmap_single(ndev->dev.parent, cur_p->phys,
					 (cur_p->cntrl &
					  XAXIDMA_BD_CTRL_LENGTH_MASK),
					 DMA_TO_DEVICE);
		if (cur_p->app4)
			dev_kfree_skb_irq((struct sk_buff *) cur_p->app4);
		cur_p->phys = 0;
		cur_p->cntrl = 0;
		cur_p->status = 0;
		cur_p->app0 = 0;
		cur_p->app1 = 0;
		cur_p->app2 = 0;
		cur_p->app3 = 0;
		cur_p->app4 = 0;
		cur_p->sw_id_offset = 0;
	}

	for (i = 0; i < RX_BD_NUM; i++) {
		cur_p = &lp->rx_bd_v[i];
		cur_p->status = 0;
		cur_p->app0 = 0;
		cur_p->app1 = 0;
		cur_p->app2 = 0;
		cur_p->app3 = 0;
		cur_p->app4 = 0;
	}

	lp->tx_bd_ci = 0;
	lp->tx_bd_tail = 0;
	lp->rx_bd_ci = 0;

	/* Start updating the Rx channel control register */
	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	/* Update the interrupt coalesce count */
	cr = ((cr & ~XAXIDMA_COALESCE_MASK) |
	      (XAXIDMA_DFT_RX_THRESHOLD << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay timer count */
	cr = ((cr & ~XAXIDMA_DELAY_MASK) |
	      (XAXIDMA_DFT_RX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay timer and error interrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Finally write to the Rx channel control register */
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET, cr);

	/* Start updating the Tx channel control register */
	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	/* Update the interrupt coalesce count */
	cr = (((cr & ~XAXIDMA_COALESCE_MASK)) |
	      (XAXIDMA_DFT_TX_THRESHOLD << XAXIDMA_COALESCE_SHIFT));
	/* Update the delay timer count */
	cr = (((cr & ~XAXIDMA_DELAY_MASK)) |
	      (XAXIDMA_DFT_TX_WAITBOUND << XAXIDMA_DELAY_SHIFT));
	/* Enable coalesce, delay timer and error interrupts */
	cr |= XAXIDMA_IRQ_ALL_MASK;
	/* Finally write to the Tx channel control register */
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET, cr);

	/* Populate the tail pointer and bring the Rx Axi DMA engine out of
	 * halted state. This will make the Rx side ready for reception.
	 */
	axienet_dma_out32(lp, XAXIDMA_RX_CDESC_OFFSET, lp->rx_bd_p);
	cr = axienet_dma_in32(lp, XAXIDMA_RX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_RX_CR_OFFSET,
			  cr | XAXIDMA_CR_RUNSTOP_MASK);
	axienet_dma_out32(lp, XAXIDMA_RX_TDESC_OFFSET, lp->rx_bd_p +
			  (sizeof(*lp->rx_bd_v) * (RX_BD_NUM - 1)));

	/* Write to the RS (Run-stop) bit in the Tx channel control register.
	 * Tx channel is now ready to run. But only after we write to the
	 * tail pointer register that the Tx channel will start transmitting
	 */
	axienet_dma_out32(lp, XAXIDMA_TX_CDESC_OFFSET, lp->tx_bd_p);
	cr = axienet_dma_in32(lp, XAXIDMA_TX_CR_OFFSET);
	axienet_dma_out32(lp, XAXIDMA_TX_CR_OFFSET,
			  cr | XAXIDMA_CR_RUNSTOP_MASK);

	axienet_status = axienet_ior(lp, XAE_RCW1_OFFSET);
	axienet_status &= ~XAE_RCW1_RX_MASK;
	axienet_iow(lp, XAE_RCW1_OFFSET, axienet_status);

	axienet_status = axienet_ior(lp, XAE_IP_OFFSET);
	if (axienet_status & XAE_INT_RXRJECT_MASK)
		axienet_iow(lp, XAE_IS_OFFSET, XAE_INT_RXRJECT_MASK);
	axienet_iow(lp, XAE_FCC_OFFSET, XAE_FCC_FCRX_MASK);

	/* Sync default options with HW but leave receiver and
	 * transmitter disabled.
	 */
	axienet_setoptions(ndev, lp->options &
			   ~(XAE_OPTION_TXEN | XAE_OPTION_RXEN));
	axienet_set_mac_address(ndev, NULL);
	axienet_set_multicast_list(ndev);
	axienet_setoptions(ndev, lp->options);
}