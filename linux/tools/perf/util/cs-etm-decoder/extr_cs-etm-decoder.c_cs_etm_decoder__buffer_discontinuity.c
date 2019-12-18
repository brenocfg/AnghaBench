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
typedef  int /*<<< orphan*/  uint8_t ;
struct cs_etm_packet_queue {int dummy; } ;
typedef  int /*<<< orphan*/  ocsd_datapath_resp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_DISCONTINUITY ; 
 int /*<<< orphan*/  cs_etm_decoder__buffer_packet (struct cs_etm_packet_queue*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm_decoder__reset_timestamp (struct cs_etm_packet_queue*) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__buffer_discontinuity(struct cs_etm_packet_queue *queue,
				     const uint8_t trace_chan_id)
{
	/*
	 * Something happened and who knows when we'll get new traces so
	 * reset time statistics.
	 */
	cs_etm_decoder__reset_timestamp(queue);
	return cs_etm_decoder__buffer_packet(queue, trace_chan_id,
					     CS_ETM_DISCONTINUITY);
}