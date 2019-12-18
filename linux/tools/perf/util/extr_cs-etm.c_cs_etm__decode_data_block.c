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
struct cs_etm_queue {size_t offset; size_t buf_used; size_t buf_len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  decoder; } ;

/* Variables and functions */
 int cs_etm_decoder__process_data_block (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t,size_t*) ; 

__attribute__((used)) static int cs_etm__decode_data_block(struct cs_etm_queue *etmq)
{
	int ret = 0;
	size_t processed = 0;

	/*
	 * Packets are decoded and added to the decoder's packet queue
	 * until the decoder packet processing callback has requested that
	 * processing stops or there is nothing left in the buffer.  Normal
	 * operations that stop processing are a timestamp packet or a full
	 * decoder buffer queue.
	 */
	ret = cs_etm_decoder__process_data_block(etmq->decoder,
						 etmq->offset,
						 &etmq->buf[etmq->buf_used],
						 etmq->buf_len,
						 &processed);
	if (ret)
		goto out;

	etmq->offset += processed;
	etmq->buf_used += processed;
	etmq->buf_len -= processed;

out:
	return ret;
}