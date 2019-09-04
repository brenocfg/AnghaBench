#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* pci_dev; } ;
struct hpi_adapter_obj {TYPE_2__ pci; } ;
struct TYPE_3__ {int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI6205_ERROR_DSP_EXTMEM ; 
 scalar_t__ boot_loader_test_memory (struct hpi_adapter_obj*,int,int,int) ; 

__attribute__((used)) static u16 boot_loader_test_external_memory(struct hpi_adapter_obj *pao,
	int dsp_index)
{
	u32 dRAM_start_address = 0;
	u32 dRAM_size = 0;

	if (dsp_index == 0) {
		/* only test for SDRAM if an ASI5000 card */
		if (pao->pci.pci_dev->subsystem_device == 0x5000) {
			/* DSP 0 is always C6205 */
			dRAM_start_address = 0x00400000;
			dRAM_size = 0x200000;
			/*dwDRAMinc=1024; */
		} else
			return 0;
	} else if (dsp_index == 1) {
		/* DSP 1 is a C6713 */
		dRAM_start_address = 0x80000000;
		dRAM_size = 0x200000;
		/*dwDRAMinc=1024; */
	}

	if (boot_loader_test_memory(pao, dsp_index, dRAM_start_address,
			dRAM_size))
		return HPI6205_ERROR_DSP_EXTMEM;
	return 0;
}