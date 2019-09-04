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
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_packet {scalar_t__ sample_type; int /*<<< orphan*/  start_addr; } ;

/* Variables and functions */
 scalar_t__ CS_ETM_TRACE_ON ; 

__attribute__((used)) static inline u64 cs_etm__first_executed_instr(struct cs_etm_packet *packet)
{
	/* Returns 0 for the CS_ETM_TRACE_ON packet */
	if (packet->sample_type == CS_ETM_TRACE_ON)
		return 0;

	return packet->start_addr;
}