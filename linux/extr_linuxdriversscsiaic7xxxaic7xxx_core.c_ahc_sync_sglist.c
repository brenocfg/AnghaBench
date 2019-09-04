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
struct scb {int sg_count; int sg_list; TYPE_2__* sg_map; } ;
struct ahc_softc {TYPE_1__* scb_data; } ;
struct ahc_dma_seg {int dummy; } ;
struct TYPE_4__ {int sg_vaddr; int /*<<< orphan*/  sg_dmamap; } ;
struct TYPE_3__ {int /*<<< orphan*/  sg_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahc_dmamap_sync (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

void
ahc_sync_sglist(struct ahc_softc *ahc, struct scb *scb, int op)
{
	if (scb->sg_count == 0)
		return;

	ahc_dmamap_sync(ahc, ahc->scb_data->sg_dmat, scb->sg_map->sg_dmamap,
			/*offset*/(scb->sg_list - scb->sg_map->sg_vaddr)
				* sizeof(struct ahc_dma_seg),
			/*len*/sizeof(struct ahc_dma_seg) * scb->sg_count, op);
}