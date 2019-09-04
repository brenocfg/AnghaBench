#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  address; } ;
struct TYPE_5__ {TYPE_1__ a64; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct mem_array {int /*<<< orphan*/  size; TYPE_3__ bus_address; int /*<<< orphan*/  virtual_address; } ;
struct beiscsi_hba {int dummy; } ;
struct be_dma_mem {scalar_t__ va; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_sgl_create_contiguous (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct be_dma_mem*) ; 
 int /*<<< orphan*/  be_sgl_destroy_contiguous (struct be_dma_mem*) ; 

__attribute__((used)) static void
hwi_build_be_sgl_arr(struct beiscsi_hba *phba,
		     struct mem_array *pmem, struct be_dma_mem *sgl)
{
	if (sgl->va)
		be_sgl_destroy_contiguous(sgl);

	be_sgl_create_contiguous(pmem->virtual_address,
				 pmem->bus_address.u.a64.address,
				 pmem->size, sgl);
}