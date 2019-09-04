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
struct mt76u_buf {int /*<<< orphan*/  urb; } ;
struct mt76_queue {int buf_size; } ;
struct mt76_dev {struct mt76_queue* q_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MT_EP_IN_PKT_RX ; 
 size_t MT_RXQ_MAIN ; 
 int /*<<< orphan*/  SKB_WITH_OVERHEAD (int) ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  mt76_rx_poll_complete (struct mt76_dev*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76u_complete_rx ; 
 int mt76u_fill_rx_sg (struct mt76_dev*,struct mt76u_buf*,int,int,int /*<<< orphan*/ ) ; 
 struct mt76u_buf* mt76u_get_next_rx_entry (struct mt76_queue*) ; 
 int mt76u_process_rx_entry (struct mt76_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76u_submit_buf (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76u_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt76_dev*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void mt76u_rx_tasklet(unsigned long data)
{
	struct mt76_dev *dev = (struct mt76_dev *)data;
	struct mt76_queue *q = &dev->q_rx[MT_RXQ_MAIN];
	int err, nsgs, buf_len = q->buf_size;
	struct mt76u_buf *buf;

	rcu_read_lock();

	while (true) {
		buf = mt76u_get_next_rx_entry(q);
		if (!buf)
			break;

		nsgs = mt76u_process_rx_entry(dev, buf->urb);
		if (nsgs > 0) {
			err = mt76u_fill_rx_sg(dev, buf, nsgs,
					       buf_len,
					       SKB_WITH_OVERHEAD(buf_len));
			if (err < 0)
				break;
		}
		mt76u_submit_buf(dev, USB_DIR_IN, MT_EP_IN_PKT_RX,
				 buf, GFP_ATOMIC,
				 mt76u_complete_rx, dev);
	}
	mt76_rx_poll_complete(dev, MT_RXQ_MAIN, NULL);

	rcu_read_unlock();
}