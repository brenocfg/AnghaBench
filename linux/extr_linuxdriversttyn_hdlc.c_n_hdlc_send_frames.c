#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  flags; int /*<<< orphan*/  write_wait; TYPE_1__* ops; } ;
struct n_hdlc_buf {int count; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  spinlock; } ;
struct n_hdlc {int tbusy; int woke_up; TYPE_2__ tx_buf_list; int /*<<< orphan*/  tx_free_buf_list; } ;
struct TYPE_4__ {int (* write ) (struct tty_struct*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ debuglevel ; 
 struct n_hdlc_buf* n_hdlc_buf_get (TYPE_2__*) ; 
 int /*<<< orphan*/  n_hdlc_buf_put (int /*<<< orphan*/ *,struct n_hdlc_buf*) ; 
 int /*<<< orphan*/  n_hdlc_buf_return (TYPE_2__*,struct n_hdlc_buf*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct tty_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void n_hdlc_send_frames(struct n_hdlc *n_hdlc, struct tty_struct *tty)
{
	register int actual;
	unsigned long flags;
	struct n_hdlc_buf *tbuf;

	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("%s(%d)n_hdlc_send_frames() called\n",__FILE__,__LINE__);
 check_again:
		
 	spin_lock_irqsave(&n_hdlc->tx_buf_list.spinlock, flags);
	if (n_hdlc->tbusy) {
		n_hdlc->woke_up = 1;
 		spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags);
		return;
	}
	n_hdlc->tbusy = 1;
	n_hdlc->woke_up = 0;
	spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags);

	tbuf = n_hdlc_buf_get(&n_hdlc->tx_buf_list);
	while (tbuf) {
		if (debuglevel >= DEBUG_LEVEL_INFO)	
			printk("%s(%d)sending frame %p, count=%d\n",
				__FILE__,__LINE__,tbuf,tbuf->count);
			
		/* Send the next block of data to device */
		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		actual = tty->ops->write(tty, tbuf->buf, tbuf->count);

		/* rollback was possible and has been done */
		if (actual == -ERESTARTSYS) {
			n_hdlc_buf_return(&n_hdlc->tx_buf_list, tbuf);
			break;
		}
		/* if transmit error, throw frame away by */
		/* pretending it was accepted by driver */
		if (actual < 0)
			actual = tbuf->count;
		
		if (actual == tbuf->count) {
			if (debuglevel >= DEBUG_LEVEL_INFO)	
				printk("%s(%d)frame %p completed\n",
					__FILE__,__LINE__,tbuf);
					
			/* free current transmit buffer */
			n_hdlc_buf_put(&n_hdlc->tx_free_buf_list, tbuf);

			/* wait up sleeping writers */
			wake_up_interruptible(&tty->write_wait);
	
			/* get next pending transmit buffer */
			tbuf = n_hdlc_buf_get(&n_hdlc->tx_buf_list);
		} else {
			if (debuglevel >= DEBUG_LEVEL_INFO)	
				printk("%s(%d)frame %p pending\n",
					__FILE__,__LINE__,tbuf);

			/*
			 * the buffer was not accepted by driver,
			 * return it back into tx queue
			 */
			n_hdlc_buf_return(&n_hdlc->tx_buf_list, tbuf);
			break;
		}
	}
	
	if (!tbuf)
		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	
	/* Clear the re-entry flag */
	spin_lock_irqsave(&n_hdlc->tx_buf_list.spinlock, flags);
	n_hdlc->tbusy = 0;
	spin_unlock_irqrestore(&n_hdlc->tx_buf_list.spinlock, flags); 
	
        if (n_hdlc->woke_up)
	  goto check_again;

	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("%s(%d)n_hdlc_send_frames() exit\n",__FILE__,__LINE__);
		
}