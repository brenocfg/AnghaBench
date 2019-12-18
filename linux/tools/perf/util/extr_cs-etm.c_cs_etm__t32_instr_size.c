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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  cs_etm__mem_access (struct cs_etm_queue*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int cs_etm__t32_instr_size(struct cs_etm_queue *etmq,
					 u8 trace_chan_id, u64 addr)
{
	u8 instrBytes[2];

	cs_etm__mem_access(etmq, trace_chan_id, addr,
			   ARRAY_SIZE(instrBytes), instrBytes);
	/*
	 * T32 instruction size is indicated by bits[15:11] of the first
	 * 16-bit word of the instruction: 0b11101, 0b11110 and 0b11111
	 * denote a 32-bit instruction.
	 */
	return ((instrBytes[1] & 0xF8) >= 0xE8) ? 4 : 2;
}