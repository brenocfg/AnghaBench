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
struct tty_struct {struct n_hdlc_buf* disc_data; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; } ;
struct n_hdlc_buf {int /*<<< orphan*/  tx_buf_list; int /*<<< orphan*/  rx_buf_list; int /*<<< orphan*/  tx_free_buf_list; int /*<<< orphan*/  rx_free_buf_list; } ;
struct n_hdlc {int /*<<< orphan*/  tx_buf_list; int /*<<< orphan*/  rx_buf_list; int /*<<< orphan*/  tx_free_buf_list; int /*<<< orphan*/  rx_free_buf_list; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debuglevel ; 
 int /*<<< orphan*/  kfree (struct n_hdlc_buf*) ; 
 struct tty_struct* n_hdlc2tty (struct n_hdlc_buf*) ; 
 struct n_hdlc_buf* n_hdlc_buf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void n_hdlc_release(struct n_hdlc *n_hdlc)
{
	struct tty_struct *tty = n_hdlc2tty (n_hdlc);
	struct n_hdlc_buf *buf;
	
	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("%s(%d)n_hdlc_release() called\n",__FILE__,__LINE__);
		
	/* Ensure that the n_hdlcd process is not hanging on select()/poll() */
	wake_up_interruptible (&tty->read_wait);
	wake_up_interruptible (&tty->write_wait);

	if (tty->disc_data == n_hdlc)
		tty->disc_data = NULL;	/* Break the tty->n_hdlc link */

	/* Release transmit and receive buffers */
	for(;;) {
		buf = n_hdlc_buf_get(&n_hdlc->rx_free_buf_list);
		if (buf) {
			kfree(buf);
		} else
			break;
	}
	for(;;) {
		buf = n_hdlc_buf_get(&n_hdlc->tx_free_buf_list);
		if (buf) {
			kfree(buf);
		} else
			break;
	}
	for(;;) {
		buf = n_hdlc_buf_get(&n_hdlc->rx_buf_list);
		if (buf) {
			kfree(buf);
		} else
			break;
	}
	for(;;) {
		buf = n_hdlc_buf_get(&n_hdlc->tx_buf_list);
		if (buf) {
			kfree(buf);
		} else
			break;
	}
	kfree(n_hdlc);
	
}