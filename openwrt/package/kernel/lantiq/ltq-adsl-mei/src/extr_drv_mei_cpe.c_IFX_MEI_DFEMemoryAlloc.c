#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* address; char* org_address; int size; } ;
typedef  TYPE_1__ smmu_mem_info_t ;
struct TYPE_7__ {TYPE_1__* adsl_mem_info; } ;
typedef  TYPE_2__ ifx_mei_device_private_t ;
struct TYPE_8__ {scalar_t__ pPriv; } ;
typedef  TYPE_3__ DSL_DEV_Device_t ;

/* Variables and functions */
 int EFBIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREE_ALL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFX_MEI_DFEMemoryFree (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_DMSG (char*,long) ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,...) ; 
 int MAX_BAR_REGISTERS ; 
 long SDRAM_SEGMENT_SIZE ; 
 int XDATA_REGISTER ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
IFX_MEI_DFEMemoryAlloc (DSL_DEV_Device_t * pDev, long size)
{
	unsigned long mem_ptr;
	char *org_mem_ptr = NULL;
	int idx = 0;
	long total_size = 0;
	int err = 0;
	smmu_mem_info_t *adsl_mem_info =
		((ifx_mei_device_private_t *) pDev->pPriv)->adsl_mem_info;
//		DSL_DEV_PRIVATE(pDev)->adsl_mem_info;
	int allocate_size = SDRAM_SEGMENT_SIZE;

	IFX_MEI_DMSG("image_size = %ld\n", size);
	// Alloc Swap Pages
	for (idx = 0; size > 0 && idx < MAX_BAR_REGISTERS; idx++) {
		// skip bar15 for XDATA usage.
		if (idx == XDATA_REGISTER)
			continue;
#if 0
                if (size < SDRAM_SEGMENT_SIZE) {
                        allocate_size = size;
                        if (allocate_size < 1024)
                                allocate_size = 1024;
                }
#endif
                if (idx == (MAX_BAR_REGISTERS - 1))
                        allocate_size = size;
                else
                        allocate_size = SDRAM_SEGMENT_SIZE;
        
		org_mem_ptr = kmalloc (allocate_size, GFP_KERNEL);
		if (org_mem_ptr == NULL) {
                        IFX_MEI_EMSG ("%d: kmalloc %d bytes memory fail!\n", idx, allocate_size);
			err = -ENOMEM;
			goto allocate_error;
		}
		
		if (((unsigned long)org_mem_ptr) & (1023)) {
			/* Pointer not 1k aligned, so free it and allocate a larger chunk
			 * for further alignment.
			 */
			kfree(org_mem_ptr);
			org_mem_ptr = kmalloc (allocate_size + 1024, GFP_KERNEL);
			if (org_mem_ptr == NULL) {
				IFX_MEI_EMSG ("%d: kmalloc %d bytes memory fail!\n",
				              idx, allocate_size + 1024);
				err = -ENOMEM;
				goto allocate_error;
			}
			mem_ptr = (unsigned long) (org_mem_ptr + 1023) & ~(1024 -1);
		} else {
			mem_ptr = (unsigned long) org_mem_ptr;
		}

                adsl_mem_info[idx].address = (char *) mem_ptr;
                adsl_mem_info[idx].org_address = org_mem_ptr;
                adsl_mem_info[idx].size = allocate_size;
                size -= allocate_size;
                total_size += allocate_size;
	}
	if (size > 0) {
		IFX_MEI_EMSG ("Image size is too large!\n");
		err = -EFBIG;
		goto allocate_error;
	}
	err = idx;
	return err;

      allocate_error:
	IFX_MEI_DFEMemoryFree (pDev, FREE_ALL);
	return err;
}