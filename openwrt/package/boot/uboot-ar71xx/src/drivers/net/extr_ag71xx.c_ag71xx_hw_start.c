#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct eth_device {scalar_t__ priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  descs_dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  descs_dma; } ;
struct ag71xx {int link; int duplex; TYPE_3__* dev; int /*<<< orphan*/  speed; scalar_t__ phyfixed; TYPE_2__ rx_ring; TYPE_1__ tx_ring; } ;
typedef  int /*<<< orphan*/  bd_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  enetaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_RX_CTRL ; 
 int /*<<< orphan*/  AG71XX_REG_RX_DESC ; 
 int /*<<< orphan*/  AG71XX_REG_TX_DESC ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_CTRL_RXE ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  ag71xx_dma_reset (struct ag71xx*) ; 
 scalar_t__ ag71xx_getMiiSpeed (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_set_macaddr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_link_adjust (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_ring_rx_clean (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_ring_tx_init (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_rr (struct ag71xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ag71xx_hw_start(struct eth_device *dev, bd_t * bd)
{
	struct ag71xx *ag = (struct ag71xx *) dev->priv;

	ag71xx_dma_reset(ag);

    ag71xx_ring_rx_clean(ag);
	ag71xx_ring_tx_init(ag);
	
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, 
				(u32) virt_to_phys(ag->tx_ring.descs_dma));
	ag71xx_wr(ag, AG71XX_REG_RX_DESC,
				(u32) virt_to_phys(ag->rx_ring.descs_dma));

	ag71xx_hw_set_macaddr(ag, ag->dev->enetaddr);

    if (ag->phyfixed) {
        ag->link = 1;
        ag->duplex = 1;
        ag->speed = SPEED_1000;
    } else {

#if (defined(CONFIG_MII) || defined(CONFIG_CMD_MII))
		if (ag71xx_getMiiSpeed(ag))
			return -1;
#else
		/* only fixed, without mii */
		return -1;
#endif

    }
    ag71xx_link_adjust(ag);
	
	DBG("%s: txdesc reg: %#08x rxdesc reg: %#08x\n",
		ag->dev->name,
		ag71xx_rr(ag, AG71XX_REG_TX_DESC),
		ag71xx_rr(ag, AG71XX_REG_RX_DESC));
	
	/* start RX engine */
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, RX_CTRL_RXE);
	
	return 0;
}