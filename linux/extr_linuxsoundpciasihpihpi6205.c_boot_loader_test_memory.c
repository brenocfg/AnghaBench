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
typedef  int u32 ;
typedef  int u16 ;
struct hpi_adapter_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  VERBOSE ; 
 int boot_loader_read_mem32 (struct hpi_adapter_obj*,int,int) ; 
 int /*<<< orphan*/  boot_loader_write_mem32 (struct hpi_adapter_obj*,int,int,int) ; 

__attribute__((used)) static u16 boot_loader_test_memory(struct hpi_adapter_obj *pao, int dsp_index,
	u32 start_address, u32 length)
{
	u32 i = 0, j = 0;
	u32 test_addr = 0;
	u32 test_data = 0, data = 0;

	length = 1000;

	/* for 1st word, test each bit in the 32bit word, */
	/* dwLength specifies number of 32bit words to test */
	/*for(i=0; i<dwLength; i++) */
	i = 0;
	{
		test_addr = start_address + i * 4;
		test_data = 0x00000001;
		for (j = 0; j < 32; j++) {
			boot_loader_write_mem32(pao, dsp_index, test_addr,
				test_data);
			data = boot_loader_read_mem32(pao, dsp_index,
				test_addr);
			if (data != test_data) {
				HPI_DEBUG_LOG(VERBOSE,
					"Memtest error details  "
					"%08x %08x %08x %i\n", test_addr,
					test_data, data, dsp_index);
				return 1;	/* error */
			}
			test_data = test_data << 1;
		}	/* for(j) */
	}	/* for(i) */

	/* for the next 100 locations test each location, leaving it as zero */
	/* write a zero to the next word in memory before we read */
	/* the previous write to make sure every memory location is unique */
	for (i = 0; i < 100; i++) {
		test_addr = start_address + i * 4;
		test_data = 0xA5A55A5A;
		boot_loader_write_mem32(pao, dsp_index, test_addr, test_data);
		boot_loader_write_mem32(pao, dsp_index, test_addr + 4, 0);
		data = boot_loader_read_mem32(pao, dsp_index, test_addr);
		if (data != test_data) {
			HPI_DEBUG_LOG(VERBOSE,
				"Memtest error details  "
				"%08x %08x %08x %i\n", test_addr, test_data,
				data, dsp_index);
			return 1;	/* error */
		}
		/* leave location as zero */
		boot_loader_write_mem32(pao, dsp_index, test_addr, 0x0);
	}

	/* zero out entire memory block */
	for (i = 0; i < length; i++) {
		test_addr = start_address + i * 4;
		boot_loader_write_mem32(pao, dsp_index, test_addr, 0x0);
	}
	return 0;
}