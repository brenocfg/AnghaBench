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
typedef  int uint32_t ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; } ;
struct deliver_completeQ {int dummy; } ;
struct MessageUnit_D {void* msgcode_rwbuffer; void* message_rbuffer; void* message_wbuffer; void* outboundlist_interrupt_enable; void* outboundlist_interrupt_cause; void* outboundlist_read_pointer; void* outboundlist_copy_pointer; void* outboundlist_base_high; void* outboundlist_base_low; void* inboundlist_write_pointer; void* inboundlist_base_high; void* inboundlist_base_low; void* outbound_doorbell_enable; void* outbound_doorbell; void* inbound_doorbell; void* outbound_msgaddr1; void* outbound_msgaddr0; void* inbound_msgaddr1; void* inbound_msgaddr0; void* pcief0_int_enable; void* host_int_status; void* reset_request; void* sample_at_reset; void* i2o_host_interrupt_mask; void* cpu_mem_config; void* chip_id; } ;
struct MessageUnit_B {void* message_rwbuffer; void* message_rbuffer; void* message_wbuffer; void* iop2drv_doorbell_mask; void* iop2drv_doorbell; void* drv2iop_doorbell_mask; void* drv2iop_doorbell; } ;
struct AdapterControlBlock {int adapter_type; int roundup_ccbsize; int completionQ_entry; int /*<<< orphan*/  doneq_index; void* pCompletionQ; void* dma_coherent2; void* dma_coherent_handle2; TYPE_1__* host; struct MessageUnit_D* pmuD; struct pci_dev* pdev; struct MessageUnit_B* pmuB; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_B 130 
#define  ACB_ADAPTER_TYPE_D 129 
#define  ACB_ADAPTER_TYPE_E 128 
 int /*<<< orphan*/  ARCMSR_ARC1214_CHIP_ID ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_CPU_MEMORY_CONFIGURATION ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_I2_HOST_INTERRUPT_MASK ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_LIST_BASE_HIGH ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_LIST_BASE_LOW ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_LIST_WRITE_POINTER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_MESSAGE0 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_INBOUND_MESSAGE1 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MAIN_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MESSAGE_RBUFFER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MESSAGE_RWBUFFER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_MESSAGE_WBUFFER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_DOORBELL_ENABLE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_INTERRUPT_CAUSE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_BASE_HIGH ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_BASE_LOW ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_COPY_POINTER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_LIST_READ_POINTER ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_MESSAGE0 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_OUTBOUND_MESSAGE1 ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_PCIE_F0_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_RESET_REQUEST ; 
 int /*<<< orphan*/  ARCMSR_ARC1214_SAMPLE_RESET ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL_1203 ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL_MASK ; 
 int /*<<< orphan*/  ARCMSR_DRV2IOP_DOORBELL_MASK_1203 ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL_1203 ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL_MASK ; 
 int /*<<< orphan*/  ARCMSR_IOP2DRV_DOORBELL_MASK_1203 ; 
 int ARCMSR_MAX_HBE_DONEQUEUE ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_RBUFFER ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_RWBUFFER ; 
 int /*<<< orphan*/  ARCMSR_MESSAGE_WBUFFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MEM_BASE0 (int /*<<< orphan*/ ) ; 
 void* MEM_BASE1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_ARECA_1203 ; 
 void* dma_zalloc_coherent (int /*<<< orphan*/ *,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 void* roundup (int,int) ; 

__attribute__((used)) static bool arcmsr_alloc_io_queue(struct AdapterControlBlock *acb)
{
	bool rtn = true;
	void *dma_coherent;
	dma_addr_t dma_coherent_handle;
	struct pci_dev *pdev = acb->pdev;

	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_B: {
		struct MessageUnit_B *reg;
		acb->roundup_ccbsize = roundup(sizeof(struct MessageUnit_B), 32);
		dma_coherent = dma_zalloc_coherent(&pdev->dev, acb->roundup_ccbsize,
			&dma_coherent_handle, GFP_KERNEL);
		if (!dma_coherent) {
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			return false;
		}
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		reg = (struct MessageUnit_B *)dma_coherent;
		acb->pmuB = reg;
		if (acb->pdev->device == PCI_DEVICE_ID_ARECA_1203) {
			reg->drv2iop_doorbell = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_1203);
			reg->drv2iop_doorbell_mask = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_MASK_1203);
			reg->iop2drv_doorbell = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_1203);
			reg->iop2drv_doorbell_mask = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_MASK_1203);
		} else {
			reg->drv2iop_doorbell = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL);
			reg->drv2iop_doorbell_mask = MEM_BASE0(ARCMSR_DRV2IOP_DOORBELL_MASK);
			reg->iop2drv_doorbell = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL);
			reg->iop2drv_doorbell_mask = MEM_BASE0(ARCMSR_IOP2DRV_DOORBELL_MASK);
		}
		reg->message_wbuffer = MEM_BASE1(ARCMSR_MESSAGE_WBUFFER);
		reg->message_rbuffer = MEM_BASE1(ARCMSR_MESSAGE_RBUFFER);
		reg->message_rwbuffer = MEM_BASE1(ARCMSR_MESSAGE_RWBUFFER);
		}
		break;
	case ACB_ADAPTER_TYPE_D: {
		struct MessageUnit_D *reg;

		acb->roundup_ccbsize = roundup(sizeof(struct MessageUnit_D), 32);
		dma_coherent = dma_zalloc_coherent(&pdev->dev, acb->roundup_ccbsize,
			&dma_coherent_handle, GFP_KERNEL);
		if (!dma_coherent) {
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			return false;
		}
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		reg = (struct MessageUnit_D *)dma_coherent;
		acb->pmuD = reg;
		reg->chip_id = MEM_BASE0(ARCMSR_ARC1214_CHIP_ID);
		reg->cpu_mem_config = MEM_BASE0(ARCMSR_ARC1214_CPU_MEMORY_CONFIGURATION);
		reg->i2o_host_interrupt_mask = MEM_BASE0(ARCMSR_ARC1214_I2_HOST_INTERRUPT_MASK);
		reg->sample_at_reset = MEM_BASE0(ARCMSR_ARC1214_SAMPLE_RESET);
		reg->reset_request = MEM_BASE0(ARCMSR_ARC1214_RESET_REQUEST);
		reg->host_int_status = MEM_BASE0(ARCMSR_ARC1214_MAIN_INTERRUPT_STATUS);
		reg->pcief0_int_enable = MEM_BASE0(ARCMSR_ARC1214_PCIE_F0_INTERRUPT_ENABLE);
		reg->inbound_msgaddr0 = MEM_BASE0(ARCMSR_ARC1214_INBOUND_MESSAGE0);
		reg->inbound_msgaddr1 = MEM_BASE0(ARCMSR_ARC1214_INBOUND_MESSAGE1);
		reg->outbound_msgaddr0 = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_MESSAGE0);
		reg->outbound_msgaddr1 = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_MESSAGE1);
		reg->inbound_doorbell = MEM_BASE0(ARCMSR_ARC1214_INBOUND_DOORBELL);
		reg->outbound_doorbell = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_DOORBELL);
		reg->outbound_doorbell_enable = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_DOORBELL_ENABLE);
		reg->inboundlist_base_low = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_BASE_LOW);
		reg->inboundlist_base_high = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_BASE_HIGH);
		reg->inboundlist_write_pointer = MEM_BASE0(ARCMSR_ARC1214_INBOUND_LIST_WRITE_POINTER);
		reg->outboundlist_base_low = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_BASE_LOW);
		reg->outboundlist_base_high = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_BASE_HIGH);
		reg->outboundlist_copy_pointer = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_COPY_POINTER);
		reg->outboundlist_read_pointer = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_LIST_READ_POINTER);
		reg->outboundlist_interrupt_cause = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_INTERRUPT_CAUSE);
		reg->outboundlist_interrupt_enable = MEM_BASE0(ARCMSR_ARC1214_OUTBOUND_INTERRUPT_ENABLE);
		reg->message_wbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_WBUFFER);
		reg->message_rbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_RBUFFER);
		reg->msgcode_rwbuffer = MEM_BASE0(ARCMSR_ARC1214_MESSAGE_RWBUFFER);
		}
		break;
	case ACB_ADAPTER_TYPE_E: {
		uint32_t completeQ_size;
		completeQ_size = sizeof(struct deliver_completeQ) * ARCMSR_MAX_HBE_DONEQUEUE + 128;
		acb->roundup_ccbsize = roundup(completeQ_size, 32);
		dma_coherent = dma_zalloc_coherent(&pdev->dev, acb->roundup_ccbsize,
			&dma_coherent_handle, GFP_KERNEL);
		if (!dma_coherent){
			pr_notice("arcmsr%d: DMA allocation failed\n", acb->host->host_no);
			return false;
		}
		acb->dma_coherent_handle2 = dma_coherent_handle;
		acb->dma_coherent2 = dma_coherent;
		acb->pCompletionQ = dma_coherent;
		acb->completionQ_entry = acb->roundup_ccbsize / sizeof(struct deliver_completeQ);
		acb->doneq_index = 0;
		}
		break;
	default:
		break;
	}
	return rtn;
}