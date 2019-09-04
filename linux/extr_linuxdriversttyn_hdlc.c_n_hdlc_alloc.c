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
struct n_hdlc_buf {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; int /*<<< orphan*/  spinlock; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; int /*<<< orphan*/  spinlock; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  spinlock; } ;
struct n_hdlc {scalar_t__ flags; int /*<<< orphan*/  magic; TYPE_3__ tx_free_buf_list; TYPE_3__ rx_free_buf_list; TYPE_2__ tx_buf_list; TYPE_1__ rx_buf_list; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int DEFAULT_RX_BUF_COUNT ; 
 int DEFAULT_TX_BUF_COUNT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDLC_MAGIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  N_HDLC_BUF_SIZE ; 
 scalar_t__ debuglevel ; 
 struct n_hdlc_buf* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct n_hdlc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_hdlc_buf_put (TYPE_3__*,struct n_hdlc_buf*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct n_hdlc *n_hdlc_alloc(void)
{
	struct n_hdlc_buf *buf;
	int i;
	struct n_hdlc *n_hdlc = kzalloc(sizeof(*n_hdlc), GFP_KERNEL);

	if (!n_hdlc)
		return NULL;

	spin_lock_init(&n_hdlc->rx_free_buf_list.spinlock);
	spin_lock_init(&n_hdlc->tx_free_buf_list.spinlock);
	spin_lock_init(&n_hdlc->rx_buf_list.spinlock);
	spin_lock_init(&n_hdlc->tx_buf_list.spinlock);

	INIT_LIST_HEAD(&n_hdlc->rx_free_buf_list.list);
	INIT_LIST_HEAD(&n_hdlc->tx_free_buf_list.list);
	INIT_LIST_HEAD(&n_hdlc->rx_buf_list.list);
	INIT_LIST_HEAD(&n_hdlc->tx_buf_list.list);

	/* allocate free rx buffer list */
	for(i=0;i<DEFAULT_RX_BUF_COUNT;i++) {
		buf = kmalloc(N_HDLC_BUF_SIZE, GFP_KERNEL);
		if (buf)
			n_hdlc_buf_put(&n_hdlc->rx_free_buf_list,buf);
		else if (debuglevel >= DEBUG_LEVEL_INFO)	
			printk("%s(%d)n_hdlc_alloc(), kalloc() failed for rx buffer %d\n",__FILE__,__LINE__, i);
	}
	
	/* allocate free tx buffer list */
	for(i=0;i<DEFAULT_TX_BUF_COUNT;i++) {
		buf = kmalloc(N_HDLC_BUF_SIZE, GFP_KERNEL);
		if (buf)
			n_hdlc_buf_put(&n_hdlc->tx_free_buf_list,buf);
		else if (debuglevel >= DEBUG_LEVEL_INFO)	
			printk("%s(%d)n_hdlc_alloc(), kalloc() failed for tx buffer %d\n",__FILE__,__LINE__, i);
	}
	
	/* Initialize the control block */
	n_hdlc->magic  = HDLC_MAGIC;
	n_hdlc->flags  = 0;
	
	return n_hdlc;
	
}