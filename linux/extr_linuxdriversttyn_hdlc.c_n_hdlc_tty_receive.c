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
struct tty_struct {int /*<<< orphan*/ * fasync; int /*<<< orphan*/  read_wait; } ;
struct n_hdlc_buf {int count; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct n_hdlc {scalar_t__ magic; struct tty_struct* tty; TYPE_1__ rx_buf_list; int /*<<< orphan*/  rx_free_buf_list; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HDLC_MAGIC ; 
 scalar_t__ MAX_RX_BUF_COUNT ; 
 int /*<<< orphan*/  N_HDLC_BUF_SIZE ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 scalar_t__ debuglevel ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct n_hdlc_buf* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxframe ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 struct n_hdlc_buf* n_hdlc_buf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_hdlc_buf_put (TYPE_1__*,struct n_hdlc_buf*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,...) ; 
 struct n_hdlc* tty2n_hdlc (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void n_hdlc_tty_receive(struct tty_struct *tty, const __u8 *data,
			       char *flags, int count)
{
	register struct n_hdlc *n_hdlc = tty2n_hdlc (tty);
	register struct n_hdlc_buf *buf;

	if (debuglevel >= DEBUG_LEVEL_INFO)	
		printk("%s(%d)n_hdlc_tty_receive() called count=%d\n",
			__FILE__,__LINE__, count);
		
	/* This can happen if stuff comes in on the backup tty */
	if (!n_hdlc || tty != n_hdlc->tty)
		return;
		
	/* verify line is using HDLC discipline */
	if (n_hdlc->magic != HDLC_MAGIC) {
		printk("%s(%d) line not using HDLC discipline\n",
			__FILE__,__LINE__);
		return;
	}
	
	if ( count>maxframe ) {
		if (debuglevel >= DEBUG_LEVEL_INFO)	
			printk("%s(%d) rx count>maxframesize, data discarded\n",
			       __FILE__,__LINE__);
		return;
	}

	/* get a free HDLC buffer */	
	buf = n_hdlc_buf_get(&n_hdlc->rx_free_buf_list);
	if (!buf) {
		/* no buffers in free list, attempt to allocate another rx buffer */
		/* unless the maximum count has been reached */
		if (n_hdlc->rx_buf_list.count < MAX_RX_BUF_COUNT)
			buf = kmalloc(N_HDLC_BUF_SIZE, GFP_ATOMIC);
	}
	
	if (!buf) {
		if (debuglevel >= DEBUG_LEVEL_INFO)	
			printk("%s(%d) no more rx buffers, data discarded\n",
			       __FILE__,__LINE__);
		return;
	}
		
	/* copy received data to HDLC buffer */
	memcpy(buf->buf,data,count);
	buf->count=count;

	/* add HDLC buffer to list of received frames */
	n_hdlc_buf_put(&n_hdlc->rx_buf_list, buf);
	
	/* wake up any blocked reads and perform async signalling */
	wake_up_interruptible (&tty->read_wait);
	if (n_hdlc->tty->fasync != NULL)
		kill_fasync (&n_hdlc->tty->fasync, SIGIO, POLL_IN);

}