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
struct cs_etm_packet_queue {int dummy; } ;
struct cs_etm_traceid_queue {TYPE_1__* packet; struct cs_etm_packet_queue packet_queue; } ;
struct cs_etm_queue {int dummy; } ;
struct TYPE_2__ {int sample_type; } ;

/* Variables and functions */
#define  CS_ETM_DISCONTINUITY 132 
#define  CS_ETM_EMPTY 131 
#define  CS_ETM_EXCEPTION 130 
#define  CS_ETM_EXCEPTION_RET 129 
#define  CS_ETM_RANGE 128 
 int EINVAL ; 
 int /*<<< orphan*/  cs_etm__exception (struct cs_etm_traceid_queue*) ; 
 int /*<<< orphan*/  cs_etm__flush (struct cs_etm_queue*,struct cs_etm_traceid_queue*) ; 
 int /*<<< orphan*/  cs_etm__sample (struct cs_etm_queue*,struct cs_etm_traceid_queue*) ; 
 int cs_etm__set_sample_flags (struct cs_etm_queue*,struct cs_etm_traceid_queue*) ; 
 int cs_etm_decoder__get_packet (struct cs_etm_packet_queue*,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cs_etm__process_traceid_queue(struct cs_etm_queue *etmq,
					 struct cs_etm_traceid_queue *tidq)
{
	int ret;
	struct cs_etm_packet_queue *packet_queue;

	packet_queue = &tidq->packet_queue;

	/* Process each packet in this chunk */
	while (1) {
		ret = cs_etm_decoder__get_packet(packet_queue,
						 tidq->packet);
		if (ret <= 0)
			/*
			 * Stop processing this chunk on
			 * end of data or error
			 */
			break;

		/*
		 * Since packet addresses are swapped in packet
		 * handling within below switch() statements,
		 * thus setting sample flags must be called
		 * prior to switch() statement to use address
		 * information before packets swapping.
		 */
		ret = cs_etm__set_sample_flags(etmq, tidq);
		if (ret < 0)
			break;

		switch (tidq->packet->sample_type) {
		case CS_ETM_RANGE:
			/*
			 * If the packet contains an instruction
			 * range, generate instruction sequence
			 * events.
			 */
			cs_etm__sample(etmq, tidq);
			break;
		case CS_ETM_EXCEPTION:
		case CS_ETM_EXCEPTION_RET:
			/*
			 * If the exception packet is coming,
			 * make sure the previous instruction
			 * range packet to be handled properly.
			 */
			cs_etm__exception(tidq);
			break;
		case CS_ETM_DISCONTINUITY:
			/*
			 * Discontinuity in trace, flush
			 * previous branch stack
			 */
			cs_etm__flush(etmq, tidq);
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

	return ret;
}