#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct fiq_dma_blob {TYPE_10__* channel; } ;
struct TYPE_23__ {scalar_t__ nrframes; int /*<<< orphan*/ * iso_desc; scalar_t__ index; } ;
struct TYPE_22__ {int* slot_len; scalar_t__ index; } ;
struct TYPE_21__ {scalar_t__ d32; } ;
struct TYPE_20__ {scalar_t__ d32; } ;
struct TYPE_19__ {scalar_t__ d32; } ;
struct TYPE_18__ {scalar_t__ d32; } ;
struct TYPE_17__ {scalar_t__ d32; } ;
struct TYPE_16__ {scalar_t__ d32; } ;
struct fiq_channel_state {TYPE_9__ hs_isoc_info; TYPE_8__ dma_info; scalar_t__ nrpackets; scalar_t__ expected_uframe; scalar_t__ port_addr; scalar_t__ hub_addr; scalar_t__ nr_errors; TYPE_7__ hcdma_copy; TYPE_6__ hctsiz_copy; TYPE_5__ hcintmsk_copy; TYPE_4__ hcint_copy; TYPE_3__ hcsplt_copy; TYPE_2__ hcchar_copy; int /*<<< orphan*/  fsm; } ;
struct TYPE_14__ {struct fiq_dma_blob* fiq_dmab; TYPE_1__* fiq_state; } ;
typedef  TYPE_11__ dwc_otg_hcd_t ;
struct TYPE_15__ {struct fiq_channel_state* channel; } ;
struct TYPE_13__ {int /*<<< orphan*/ * index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MEMSET (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  FIQ_PASSTHROUGH ; 

void dwc_otg_cleanup_fiq_channel(dwc_otg_hcd_t *hcd, uint32_t num)
{
	struct fiq_channel_state *st = &hcd->fiq_state->channel[num];
	struct fiq_dma_blob *blob = hcd->fiq_dmab;
	int i;

	st->fsm = FIQ_PASSTHROUGH;
	st->hcchar_copy.d32 = 0;
	st->hcsplt_copy.d32 = 0;
	st->hcint_copy.d32 = 0;
	st->hcintmsk_copy.d32 = 0;
	st->hctsiz_copy.d32 = 0;
	st->hcdma_copy.d32 = 0;
	st->nr_errors = 0;
	st->hub_addr = 0;
	st->port_addr = 0;
	st->expected_uframe = 0;
	st->nrpackets = 0;
	st->dma_info.index = 0;
	for (i = 0; i < 6; i++)
		st->dma_info.slot_len[i] = 255;
	st->hs_isoc_info.index = 0;
	st->hs_isoc_info.iso_desc = NULL;
	st->hs_isoc_info.nrframes = 0;

	DWC_MEMSET(&blob->channel[num].index[0], 0x6b, 1128);
}