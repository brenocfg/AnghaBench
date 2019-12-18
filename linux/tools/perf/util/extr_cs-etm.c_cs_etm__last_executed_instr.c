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
struct cs_etm_packet {scalar_t__ sample_type; scalar_t__ last_instr_size; scalar_t__ end_addr; } ;

/* Variables and functions */
 scalar_t__ CS_ETM_DISCONTINUITY ; 

__attribute__((used)) static inline
u64 cs_etm__last_executed_instr(const struct cs_etm_packet *packet)
{
	/* Returns 0 for the CS_ETM_DISCONTINUITY packet */
	if (packet->sample_type == CS_ETM_DISCONTINUITY)
		return 0;

	return packet->end_addr - packet->last_instr_size;
}