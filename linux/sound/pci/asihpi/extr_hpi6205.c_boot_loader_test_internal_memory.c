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
typedef  int /*<<< orphan*/  u16 ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI6205_ERROR_DSP_INTMEM ; 
 int boot_loader_test_memory (struct hpi_adapter_obj*,int,int,int) ; 

__attribute__((used)) static u16 boot_loader_test_internal_memory(struct hpi_adapter_obj *pao,
	int dsp_index)
{
	int err = 0;
	if (dsp_index == 0) {
		/* DSP 0 is a C6205 */
		/* 64K prog mem */
		err = boot_loader_test_memory(pao, dsp_index, 0x00000000,
			0x10000);
		if (!err)
			/* 64K data mem */
			err = boot_loader_test_memory(pao, dsp_index,
				0x80000000, 0x10000);
	} else if (dsp_index == 1) {
		/* DSP 1 is a C6713 */
		/* 192K internal mem */
		err = boot_loader_test_memory(pao, dsp_index, 0x00000000,
			0x30000);
		if (!err)
			/* 64K internal mem / L2 cache */
			err = boot_loader_test_memory(pao, dsp_index,
				0x00030000, 0x10000);
	}

	if (err)
		return HPI6205_ERROR_DSP_INTMEM;
	else
		return 0;
}