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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ dsp_dram_offset; scalar_t__ dram_offset; scalar_t__ dsp_iram_offset; scalar_t__ iram_offset; } ;
struct sst_dsp {TYPE_1__ addr; } ;
typedef  enum sst_mem_type { ____Placeholder_sst_mem_type } sst_mem_type ;

/* Variables and functions */
#define  SST_MEM_DRAM 129 
#define  SST_MEM_IRAM 128 

u32 sst_dsp_get_offset(struct sst_dsp *dsp, u32 offset,
	enum sst_mem_type type)
{
	switch (type) {
	case SST_MEM_IRAM:
		return offset - dsp->addr.iram_offset +
			dsp->addr.dsp_iram_offset;
	case SST_MEM_DRAM:
		return offset - dsp->addr.dram_offset +
			dsp->addr.dsp_dram_offset;
	default:
		return 0;
	}
}