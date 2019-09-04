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
typedef  int u64 ;
struct cs_etm_packet {int end_addr; int start_addr; } ;

/* Variables and functions */
 int A64_INSTR_SIZE ; 

__attribute__((used)) static inline u64 cs_etm__instr_count(const struct cs_etm_packet *packet)
{
	/*
	 * Only A64 instructions are currently supported, so can get
	 * instruction count by dividing.
	 * Will need to do instruction level decode for T32 instructions as
	 * they can be variable size (not yet supported).
	 */
	return (packet->end_addr - packet->start_addr) / A64_INSTR_SIZE;
}