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
typedef  scalar_t__ u64 ;
struct cs_etm_packet {scalar_t__ sample_type; scalar_t__ end_addr; } ;

/* Variables and functions */
 scalar_t__ A64_INSTR_SIZE ; 
 scalar_t__ CS_ETM_TRACE_ON ; 

__attribute__((used)) static inline u64 cs_etm__last_executed_instr(struct cs_etm_packet *packet)
{
	/* Returns 0 for the CS_ETM_TRACE_ON packet */
	if (packet->sample_type == CS_ETM_TRACE_ON)
		return 0;

	/*
	 * The packet records the execution range with an exclusive end address
	 *
	 * A64 instructions are constant size, so the last executed
	 * instruction is A64_INSTR_SIZE before the end address
	 * Will need to do instruction level decode for T32 instructions as
	 * they can be variable size (not yet supported).
	 */
	return packet->end_addr - A64_INSTR_SIZE;
}