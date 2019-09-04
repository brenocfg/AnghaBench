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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ScsiReqBlk {scalar_t__ total_xfer_length; int sg_index; scalar_t__ sg_count; int /*<<< orphan*/  sg_bus_addr; TYPE_2__* dcb; struct SGentry* segment_x; } ;
struct SGentry {scalar_t__ length; int /*<<< orphan*/  address; } ;
struct TYPE_4__ {TYPE_1__* acb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  SEGMENTX_LEN ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_verify_length (struct ScsiReqBlk*) ; 

__attribute__((used)) static void sg_update_list(struct ScsiReqBlk *srb, u32 left)
{
	u8 idx;
	u32 xferred = srb->total_xfer_length - left; /* bytes transferred */
	struct SGentry *psge = srb->segment_x + srb->sg_index;

	dprintkdbg(DBG_0,
		"sg_update_list: Transferred %i of %i bytes, %i remain\n",
		xferred, srb->total_xfer_length, left);
	if (xferred == 0) {
		/* nothing to update since we did not transfer any data */
		return;
	}

	sg_verify_length(srb);
	srb->total_xfer_length = left;	/* update remaining count */
	for (idx = srb->sg_index; idx < srb->sg_count; idx++) {
		if (xferred >= psge->length) {
			/* Complete SG entries done */
			xferred -= psge->length;
		} else {
			/* Partial SG entry done */
			psge->length -= xferred;
			psge->address += xferred;
			srb->sg_index = idx;
			pci_dma_sync_single_for_device(srb->dcb->
					    acb->dev,
					    srb->sg_bus_addr,
					    SEGMENTX_LEN,
					    PCI_DMA_TODEVICE);
			break;
		}
		psge++;
	}
	sg_verify_length(srb);
}