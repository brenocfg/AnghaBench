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
struct cs_etm_queue {int buf_len; int /*<<< orphan*/  decoder; } ;

/* Variables and functions */
 int cs_etm__get_trace (struct cs_etm_queue*) ; 
 int cs_etm_decoder__reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs_etm__get_data_block(struct cs_etm_queue *etmq)
{
	int ret;

	if (!etmq->buf_len) {
		ret = cs_etm__get_trace(etmq);
		if (ret <= 0)
			return ret;
		/*
		 * We cannot assume consecutive blocks in the data file
		 * are contiguous, reset the decoder to force re-sync.
		 */
		ret = cs_etm_decoder__reset(etmq->decoder);
		if (ret)
			return ret;
	}

	return etmq->buf_len;
}