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
 int /*<<< orphan*/  CS_ETM_EXCEPTION_RET ; 
 int /*<<< orphan*/  cs_etm_decoder__buffer_packet (struct cs_etm_packet_queue*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ocsd_datapath_resp_t
cs_etm_decoder__buffer_exception_ret(struct cs_etm_packet_queue *queue,
				     const uint8_t trace_chan_id)
{
	return cs_etm_decoder__buffer_packet(queue, trace_chan_id,
					     CS_ETM_EXCEPTION_RET);
}