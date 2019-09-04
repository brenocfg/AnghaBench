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
struct cosa_data {int txbitmap; int txchan; int nchannels; int txsize; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma; int /*<<< orphan*/  txbuf; scalar_t__ busmaster; int /*<<< orphan*/  rxtx; int /*<<< orphan*/  bouncebuf; TYPE_1__* chan; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int txsize; int /*<<< orphan*/  txbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_CASCADE ; 
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 int DRIVER_TXMAP_SHIFT ; 
 int /*<<< orphan*/  IRQBIT ; 
 int SR_TX_DMA_ENA ; 
 int SR_TX_INT_ENA ; 
 int SR_TX_RDY ; 
 int SR_USR_INT_ENA ; 
 int /*<<< orphan*/  TXBIT ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 scalar_t__ cosa_dma_able (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cosa_getdata8 (struct cosa_data*) ; 
 int cosa_getstatus (struct cosa_data*) ; 
 int /*<<< orphan*/  cosa_putdata16 (struct cosa_data*,unsigned long) ; 
 int /*<<< orphan*/  cosa_putdata8 (struct cosa_data*,int) ; 
 int /*<<< orphan*/  cosa_putstatus (struct cosa_data*,int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ is_8bit (struct cosa_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_driver_status_nolock (struct cosa_data*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long virt_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tx_interrupt(struct cosa_data *cosa, int status)
{
	unsigned long flags, flags1;
#ifdef DEBUG_IRQS
	pr_info("cosa%d: SR_DOWN_REQUEST status=0x%04x\n", cosa->num, status);
#endif
	spin_lock_irqsave(&cosa->lock, flags);
	set_bit(TXBIT, &cosa->rxtx);
	if (!test_bit(IRQBIT, &cosa->rxtx)) {
		/* flow control, see the comment above */
		int i=0;
		if (!cosa->txbitmap) {
			pr_warn("%s: No channel wants data in TX IRQ. Expect DMA timeout.\n",
				cosa->name);
			put_driver_status_nolock(cosa);
			clear_bit(TXBIT, &cosa->rxtx);
			spin_unlock_irqrestore(&cosa->lock, flags);
			return;
		}
		while (1) {
			cosa->txchan++;
			i++;
			if (cosa->txchan >= cosa->nchannels)
				cosa->txchan = 0;
			if (!(cosa->txbitmap & (1<<cosa->txchan)))
				continue;
			if (~status & (1 << (cosa->txchan+DRIVER_TXMAP_SHIFT)))
				break;
			/* in second pass, accept first ready-to-TX channel */
			if (i > cosa->nchannels) {
				/* Can be safely ignored */
#ifdef DEBUG_IRQS
				printk(KERN_DEBUG "%s: Forcing TX "
					"to not-ready channel %d\n",
					cosa->name, cosa->txchan);
#endif
				break;
			}
		}

		cosa->txsize = cosa->chan[cosa->txchan].txsize;
		if (cosa_dma_able(cosa->chan+cosa->txchan,
			cosa->chan[cosa->txchan].txbuf, cosa->txsize)) {
			cosa->txbuf = cosa->chan[cosa->txchan].txbuf;
		} else {
			memcpy(cosa->bouncebuf, cosa->chan[cosa->txchan].txbuf,
				cosa->txsize);
			cosa->txbuf = cosa->bouncebuf;
		}
	}

	if (is_8bit(cosa)) {
		if (!test_bit(IRQBIT, &cosa->rxtx)) {
			cosa_putstatus(cosa, SR_TX_INT_ENA);
			cosa_putdata8(cosa, ((cosa->txchan << 5) & 0xe0)|
				((cosa->txsize >> 8) & 0x1f));
#ifdef DEBUG_IO
			debug_status_out(cosa, SR_TX_INT_ENA);
			debug_data_out(cosa, ((cosa->txchan << 5) & 0xe0)|
                                ((cosa->txsize >> 8) & 0x1f));
			debug_data_in(cosa, cosa_getdata8(cosa));
#else
			cosa_getdata8(cosa);
#endif
			set_bit(IRQBIT, &cosa->rxtx);
			spin_unlock_irqrestore(&cosa->lock, flags);
			return;
		} else {
			clear_bit(IRQBIT, &cosa->rxtx);
			cosa_putstatus(cosa, 0);
			cosa_putdata8(cosa, cosa->txsize&0xff);
#ifdef DEBUG_IO
			debug_status_out(cosa, 0);
			debug_data_out(cosa, cosa->txsize&0xff);
#endif
		}
	} else {
		cosa_putstatus(cosa, SR_TX_INT_ENA);
		cosa_putdata16(cosa, ((cosa->txchan<<13) & 0xe000)
			| (cosa->txsize & 0x1fff));
#ifdef DEBUG_IO
		debug_status_out(cosa, SR_TX_INT_ENA);
		debug_data_out(cosa, ((cosa->txchan<<13) & 0xe000)
                        | (cosa->txsize & 0x1fff));
		debug_data_in(cosa, cosa_getdata8(cosa));
		debug_status_out(cosa, 0);
#else
		cosa_getdata8(cosa);
#endif
		cosa_putstatus(cosa, 0);
	}

	if (cosa->busmaster) {
		unsigned long addr = virt_to_bus(cosa->txbuf);
		int count=0;
		pr_info("busmaster IRQ\n");
		while (!(cosa_getstatus(cosa)&SR_TX_RDY)) {
			count++;
			udelay(10);
			if (count > 1000) break;
		}
		pr_info("status %x\n", cosa_getstatus(cosa));
		pr_info("ready after %d loops\n", count);
		cosa_putdata16(cosa, (addr >> 16)&0xffff);

		count = 0;
		while (!(cosa_getstatus(cosa)&SR_TX_RDY)) {
			count++;
			if (count > 1000) break;
			udelay(10);
		}
		pr_info("ready after %d loops\n", count);
		cosa_putdata16(cosa, addr &0xffff);
		flags1 = claim_dma_lock();
		set_dma_mode(cosa->dma, DMA_MODE_CASCADE);
		enable_dma(cosa->dma);
		release_dma_lock(flags1);
	} else {
		/* start the DMA */
		flags1 = claim_dma_lock();
		disable_dma(cosa->dma);
		clear_dma_ff(cosa->dma);
		set_dma_mode(cosa->dma, DMA_MODE_WRITE);
		set_dma_addr(cosa->dma, virt_to_bus(cosa->txbuf));
		set_dma_count(cosa->dma, cosa->txsize);
		enable_dma(cosa->dma);
		release_dma_lock(flags1);
	}
	cosa_putstatus(cosa, SR_TX_DMA_ENA|SR_USR_INT_ENA);
#ifdef DEBUG_IO
	debug_status_out(cosa, SR_TX_DMA_ENA|SR_USR_INT_ENA);
#endif
	spin_unlock_irqrestore(&cosa->lock, flags);
}