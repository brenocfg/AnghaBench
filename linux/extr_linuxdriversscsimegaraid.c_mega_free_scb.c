#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dma_type; int /*<<< orphan*/  list; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ scb_t ;
struct TYPE_6__ {int /*<<< orphan*/  free_list; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
#define  MEGA_DMA_TYPE_NONE 129 
#define  MEGA_SGLIST 128 
 int /*<<< orphan*/  SCB_FREE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_dma_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mega_free_scb(adapter_t *adapter, scb_t *scb)
{
	switch( scb->dma_type ) {

	case MEGA_DMA_TYPE_NONE:
		break;

	case MEGA_SGLIST:
		scsi_dma_unmap(scb->cmd);
		break;
	default:
		break;
	}

	/*
	 * Remove from the pending list
	 */
	list_del_init(&scb->list);

	/* Link the scb back into free list */
	scb->state = SCB_FREE;
	scb->cmd = NULL;

	list_add(&scb->list, &adapter->free_list);
}