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
struct tsi721_device {int /*<<< orphan*/  pw_work; scalar_t__ regs; int /*<<< orphan*/  pw_fifo_lock; int /*<<< orphan*/  pw_discard_count; int /*<<< orphan*/  pw_fifo; } ;

/* Variables and functions */
 int TSI721_RIO_PW_MSG_SIZE ; 
 scalar_t__ TSI721_RIO_PW_RX_CAPT (int) ; 
 scalar_t__ TSI721_RIO_PW_RX_STAT ; 
 int TSI721_RIO_PW_RX_STAT_PW_DISC ; 
 int TSI721_RIO_PW_RX_STAT_PW_VAL ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int kfifo_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tsi721_pw_handler(struct tsi721_device *priv)
{
	u32 pw_stat;
	u32 pw_buf[TSI721_RIO_PW_MSG_SIZE/sizeof(u32)];


	pw_stat = ioread32(priv->regs + TSI721_RIO_PW_RX_STAT);

	if (pw_stat & TSI721_RIO_PW_RX_STAT_PW_VAL) {
		pw_buf[0] = ioread32(priv->regs + TSI721_RIO_PW_RX_CAPT(0));
		pw_buf[1] = ioread32(priv->regs + TSI721_RIO_PW_RX_CAPT(1));
		pw_buf[2] = ioread32(priv->regs + TSI721_RIO_PW_RX_CAPT(2));
		pw_buf[3] = ioread32(priv->regs + TSI721_RIO_PW_RX_CAPT(3));

		/* Queue PW message (if there is room in FIFO),
		 * otherwise discard it.
		 */
		spin_lock(&priv->pw_fifo_lock);
		if (kfifo_avail(&priv->pw_fifo) >= TSI721_RIO_PW_MSG_SIZE)
			kfifo_in(&priv->pw_fifo, pw_buf,
						TSI721_RIO_PW_MSG_SIZE);
		else
			priv->pw_discard_count++;
		spin_unlock(&priv->pw_fifo_lock);
	}

	/* Clear pending PW interrupts */
	iowrite32(TSI721_RIO_PW_RX_STAT_PW_DISC | TSI721_RIO_PW_RX_STAT_PW_VAL,
		  priv->regs + TSI721_RIO_PW_RX_STAT);

	schedule_work(&priv->pw_work);

	return 0;
}