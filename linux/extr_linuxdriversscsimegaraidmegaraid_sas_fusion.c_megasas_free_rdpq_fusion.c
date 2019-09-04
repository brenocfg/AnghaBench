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
struct megasas_instance {int /*<<< orphan*/  pdev; struct fusion_context* ctrl_context; } ;
struct fusion_context {int /*<<< orphan*/  rdpq_phys; scalar_t__ rdpq_virt; scalar_t__ reply_frames_desc_pool_align; scalar_t__ reply_frames_desc_pool; TYPE_1__* rdpq_tracker; } ;
struct MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool_entry_phys; scalar_t__ pool_entry_virt; int /*<<< orphan*/  dma_pool_ptr; } ;

/* Variables and functions */
 int MAX_MSIX_QUEUES_FUSION ; 
 int RDPQ_MAX_CHUNK_COUNT ; 
 int /*<<< orphan*/  dma_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
megasas_free_rdpq_fusion(struct megasas_instance *instance) {

	int i;
	struct fusion_context *fusion;

	fusion = instance->ctrl_context;

	for (i = 0; i < RDPQ_MAX_CHUNK_COUNT; i++) {
		if (fusion->rdpq_tracker[i].pool_entry_virt)
			dma_pool_free(fusion->rdpq_tracker[i].dma_pool_ptr,
				      fusion->rdpq_tracker[i].pool_entry_virt,
				      fusion->rdpq_tracker[i].pool_entry_phys);

	}

	if (fusion->reply_frames_desc_pool)
		dma_pool_destroy(fusion->reply_frames_desc_pool);
	if (fusion->reply_frames_desc_pool_align)
		dma_pool_destroy(fusion->reply_frames_desc_pool_align);

	if (fusion->rdpq_virt)
		pci_free_consistent(instance->pdev,
			sizeof(struct MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY) * MAX_MSIX_QUEUES_FUSION,
			fusion->rdpq_virt, fusion->rdpq_phys);
}