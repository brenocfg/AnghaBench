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
typedef  int u32 ;
typedef  enum qm_memory { ____Placeholder_qm_memory } qm_memory ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int PFDR_AR_EN ; 
 int REG_FQD_BARE ; 
 int REG_PFDR_BARE ; 
 int REG_offset_AR ; 
 int REG_offset_BAR ; 
 int ilog2 (int) ; 
 scalar_t__ is_power_of_2 (int) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  qm_ccsr_out (int,int) ; 
 int qm_memory_fqd ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void qm_set_memory(enum qm_memory memory, u64 ba, u32 size)
{
	u32 offset = (memory == qm_memory_fqd) ? REG_FQD_BARE : REG_PFDR_BARE;
	u32 exp = ilog2(size);

	/* choke if size isn't within range */
	DPAA_ASSERT((size >= 4096) && (size <= 1024*1024*1024) &&
		    is_power_of_2(size));
	/* choke if 'ba' has lower-alignment than 'size' */
	DPAA_ASSERT(!(ba & (size - 1)));
	qm_ccsr_out(offset, upper_32_bits(ba));
	qm_ccsr_out(offset + REG_offset_BAR, lower_32_bits(ba));
	qm_ccsr_out(offset + REG_offset_AR, PFDR_AR_EN | (exp - 1));
}