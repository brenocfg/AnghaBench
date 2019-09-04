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
struct tty_struct {int /*<<< orphan*/  flags; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct n_hdlc {scalar_t__ magic; TYPE_2__ tx_free_buf_list; TYPE_1__ rx_buf_list; struct tty_struct* tty; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ HDLC_MAGIC ; 
 int /*<<< orphan*/  TTY_OTHER_CLOSED ; 
 scalar_t__ debuglevel ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct n_hdlc* tty2n_hdlc (struct tty_struct*) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 int /*<<< orphan*/  tty_is_writelocked (struct tty_struct*) ; 

__attribute__((used)) static __poll_t n_hdlc_tty_poll(struct tty_struct *tty, struct file *filp,
				    poll_table *wait)
{
	struct n_hdlc *n_hdlc = tty2n_hdlc (tty);
	__poll_t mask = 0;

	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("%s(%d)n_hdlc_tty_poll() called\n",__FILE__,__LINE__);
		
	if (n_hdlc && n_hdlc->magic == HDLC_MAGIC && tty == n_hdlc->tty) {
		/* queue current process into any wait queue that */
		/* may awaken in the future (read and write) */

		poll_wait(filp, &tty->read_wait, wait);
		poll_wait(filp, &tty->write_wait, wait);

		/* set bits for operations that won't block */
		if (!list_empty(&n_hdlc->rx_buf_list.list))
			mask |= EPOLLIN | EPOLLRDNORM;	/* readable */
		if (test_bit(TTY_OTHER_CLOSED, &tty->flags))
			mask |= EPOLLHUP;
		if (tty_hung_up_p(filp))
			mask |= EPOLLHUP;
		if (!tty_is_writelocked(tty) &&
				!list_empty(&n_hdlc->tx_free_buf_list.list))
			mask |= EPOLLOUT | EPOLLWRNORM;	/* writable */
	}
	return mask;
}