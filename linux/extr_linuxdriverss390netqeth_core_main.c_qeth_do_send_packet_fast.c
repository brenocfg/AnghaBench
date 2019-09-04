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
struct sk_buff {int dummy; } ;
struct qeth_qdio_out_q {int next_buf_to_fill; struct qeth_qdio_out_buffer** bufs; } ;
struct qeth_qdio_out_buffer {int /*<<< orphan*/  state; } ;
struct qeth_hdr {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 scalar_t__ QETH_QDIO_BUF_EMPTY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_fill_buffer (struct qeth_qdio_out_q*,struct qeth_qdio_out_buffer*,struct sk_buff*,struct qeth_hdr*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qeth_flush_buffers (struct qeth_qdio_out_q*,int,int) ; 

int qeth_do_send_packet_fast(struct qeth_qdio_out_q *queue, struct sk_buff *skb,
			     struct qeth_hdr *hdr, unsigned int offset,
			     unsigned int hd_len)
{
	int index = queue->next_buf_to_fill;
	struct qeth_qdio_out_buffer *buffer = queue->bufs[index];

	/*
	 * check if buffer is empty to make sure that we do not 'overtake'
	 * ourselves and try to fill a buffer that is already primed
	 */
	if (atomic_read(&buffer->state) != QETH_QDIO_BUF_EMPTY)
		return -EBUSY;
	queue->next_buf_to_fill = (index + 1) % QDIO_MAX_BUFFERS_PER_Q;
	qeth_fill_buffer(queue, buffer, skb, hdr, offset, hd_len);
	qeth_flush_buffers(queue, index, 1);
	return 0;
}