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
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_mem_desc {int phys_addr; int /*<<< orphan*/ * virt_addr; scalar_t__ esas2r_data; scalar_t__ esas2r_param; } ;
struct esas2r_adapter {TYPE_1__* pcid; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static void esas2r_initmem_free(struct esas2r_adapter *a,
				struct esas2r_mem_desc *mem_desc)
{
	if (mem_desc->virt_addr == NULL)
		return;

	/*
	 * Careful!  phys_addr and virt_addr may have been adjusted from the
	 * original allocation in order to return the desired alignment.  That
	 * means we have to use the original address (in esas2r_data) and size
	 * (esas2r_param) and calculate the original physical address based on
	 * the difference between the requested and actual allocation size.
	 */
	if (mem_desc->phys_addr) {
		int unalign = ((u8 *)mem_desc->virt_addr) -
			      ((u8 *)mem_desc->esas2r_data);

		dma_free_coherent(&a->pcid->dev,
				  (size_t)mem_desc->esas2r_param,
				  mem_desc->esas2r_data,
				  (dma_addr_t)(mem_desc->phys_addr - unalign));
	} else {
		kfree(mem_desc->esas2r_data);
	}

	mem_desc->virt_addr = NULL;
}