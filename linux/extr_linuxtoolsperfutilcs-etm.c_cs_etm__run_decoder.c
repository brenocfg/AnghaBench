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
struct cs_etm_queue {size_t offset; TYPE_1__* packet; int /*<<< orphan*/  decoder; struct cs_etm_auxtrace* etm; } ;
struct cs_etm_buffer {size_t len; int /*<<< orphan*/ * buf; } ;
struct cs_etm_auxtrace {int /*<<< orphan*/  machine; scalar_t__ kernel_start; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int sample_type; } ;

/* Variables and functions */
#define  CS_ETM_EMPTY 130 
#define  CS_ETM_RANGE 129 
#define  CS_ETM_TRACE_ON 128 
 int EINVAL ; 
 int cs_etm__flush (struct cs_etm_queue*) ; 
 int cs_etm__get_trace (struct cs_etm_buffer*,struct cs_etm_queue*) ; 
 int /*<<< orphan*/  cs_etm__sample (struct cs_etm_queue*) ; 
 int cs_etm_decoder__get_packet (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cs_etm_decoder__process_data_block (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int cs_etm_decoder__reset (int /*<<< orphan*/ ) ; 
 scalar_t__ machine__kernel_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cs_etm_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cs_etm__run_decoder(struct cs_etm_queue *etmq)
{
	struct cs_etm_auxtrace *etm = etmq->etm;
	struct cs_etm_buffer buffer;
	size_t buffer_used, processed;
	int err = 0;

	if (!etm->kernel_start)
		etm->kernel_start = machine__kernel_start(etm->machine);

	/* Go through each buffer in the queue and decode them one by one */
	while (1) {
		buffer_used = 0;
		memset(&buffer, 0, sizeof(buffer));
		err = cs_etm__get_trace(&buffer, etmq);
		if (err <= 0)
			return err;
		/*
		 * We cannot assume consecutive blocks in the data file are
		 * contiguous, reset the decoder to force re-sync.
		 */
		err = cs_etm_decoder__reset(etmq->decoder);
		if (err != 0)
			return err;

		/* Run trace decoder until buffer consumed or end of trace */
		do {
			processed = 0;
			err = cs_etm_decoder__process_data_block(
				etmq->decoder,
				etmq->offset,
				&buffer.buf[buffer_used],
				buffer.len - buffer_used,
				&processed);
			if (err)
				return err;

			etmq->offset += processed;
			buffer_used += processed;

			/* Process each packet in this chunk */
			while (1) {
				err = cs_etm_decoder__get_packet(etmq->decoder,
								 etmq->packet);
				if (err <= 0)
					/*
					 * Stop processing this chunk on
					 * end of data or error
					 */
					break;

				switch (etmq->packet->sample_type) {
				case CS_ETM_RANGE:
					/*
					 * If the packet contains an instruction
					 * range, generate instruction sequence
					 * events.
					 */
					cs_etm__sample(etmq);
					break;
				case CS_ETM_TRACE_ON:
					/*
					 * Discontinuity in trace, flush
					 * previous branch stack
					 */
					cs_etm__flush(etmq);
					break;
				case CS_ETM_EMPTY:
					/*
					 * Should not receive empty packet,
					 * report error.
					 */
					pr_err("CS ETM Trace: empty packet\n");
					return -EINVAL;
				default:
					break;
				}
			}
		} while (buffer.len > buffer_used);

		if (err == 0)
			/* Flush any remaining branch stack entries */
			err = cs_etm__flush(etmq);
	}

	return err;
}