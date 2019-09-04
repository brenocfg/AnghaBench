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
typedef  int u32 ;
struct mips_ejtag_fdc_tty_port {unsigned int xmit_cnt; int /*<<< orphan*/  xmit_lock; } ;
struct mips_ejtag_fdc_tty {int xmit_full; scalar_t__ irq; size_t xmit_next; struct mips_ejtag_fdc_tty_port* ports; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  lock; int /*<<< orphan*/  xmit_total; } ;

/* Variables and functions */
 size_t NUM_TTY_CHANNELS ; 
 int /*<<< orphan*/  REG_FDCFG ; 
 int REG_FDCFG_TXINTTHRES ; 
 int REG_FDCFG_TXINTTHRES_NOTFULL ; 
 int /*<<< orphan*/  REG_FDSTAT ; 
 int REG_FDSTAT_TXF ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 unsigned int mips_ejtag_fdc_put_chan (struct mips_ejtag_fdc_tty*,size_t) ; 
 int mips_ejtag_fdc_read (struct mips_ejtag_fdc_tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_ejtag_fdc_write (struct mips_ejtag_fdc_tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mips_ejtag_fdc_put(void *arg)
{
	struct mips_ejtag_fdc_tty *priv = arg;
	struct mips_ejtag_fdc_tty_port *dport;
	unsigned int ret;
	u32 cfg;

	__set_current_state(TASK_RUNNING);
	while (!kthread_should_stop()) {
		/* Wait for data to actually write */
		wait_event_interruptible(priv->waitqueue,
					 atomic_read(&priv->xmit_total) ||
					 kthread_should_stop());
		if (kthread_should_stop())
			break;

		/* Wait for TX FIFO space to write data */
		raw_spin_lock_irq(&priv->lock);
		if (mips_ejtag_fdc_read(priv, REG_FDSTAT) & REG_FDSTAT_TXF) {
			priv->xmit_full = true;
			if (priv->irq >= 0) {
				/* Enable TX interrupt */
				cfg = mips_ejtag_fdc_read(priv, REG_FDCFG);
				cfg &= ~REG_FDCFG_TXINTTHRES;
				cfg |= REG_FDCFG_TXINTTHRES_NOTFULL;
				mips_ejtag_fdc_write(priv, REG_FDCFG, cfg);
			}
		}
		raw_spin_unlock_irq(&priv->lock);
		wait_event_interruptible(priv->waitqueue,
					 !(mips_ejtag_fdc_read(priv, REG_FDSTAT)
					   & REG_FDSTAT_TXF) ||
					 kthread_should_stop());
		if (kthread_should_stop())
			break;

		/* Find next channel with data to output */
		for (;;) {
			dport = &priv->ports[priv->xmit_next];
			spin_lock(&dport->xmit_lock);
			ret = dport->xmit_cnt;
			spin_unlock(&dport->xmit_lock);
			if (ret)
				break;
			/* Round robin */
			++priv->xmit_next;
			if (priv->xmit_next >= NUM_TTY_CHANNELS)
				priv->xmit_next = 0;
		}

		/* Try writing data to the chosen channel */
		ret = mips_ejtag_fdc_put_chan(priv, priv->xmit_next);

		/*
		 * If anything was output, move on to the next channel so as not
		 * to starve other channels.
		 */
		if (ret) {
			++priv->xmit_next;
			if (priv->xmit_next >= NUM_TTY_CHANNELS)
				priv->xmit_next = 0;
		}
	}

	return 0;
}