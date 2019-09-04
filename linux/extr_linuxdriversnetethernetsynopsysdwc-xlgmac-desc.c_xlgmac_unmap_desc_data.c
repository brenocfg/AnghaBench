#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct xlgmac_pdata {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {scalar_t__ error; scalar_t__ len; int /*<<< orphan*/ * skb; } ;
struct TYPE_13__ {scalar_t__ pages; scalar_t__ pages_len; scalar_t__ pages_dma; } ;
struct TYPE_12__ {scalar_t__ pages; } ;
struct TYPE_14__ {TYPE_5__ pa_unmap; TYPE_4__ pa; } ;
struct TYPE_10__ {scalar_t__ pages; scalar_t__ pages_len; scalar_t__ pages_dma; } ;
struct TYPE_9__ {scalar_t__ pages; } ;
struct TYPE_11__ {TYPE_2__ pa_unmap; TYPE_1__ pa; } ;
struct TYPE_16__ {TYPE_6__ buf; TYPE_3__ hdr; } ;
struct xlgmac_desc_data {TYPE_7__ state; scalar_t__ state_saved; scalar_t__ mapped_as_page; TYPE_8__ rx; TYPE_8__ tx; int /*<<< orphan*/ * skb; scalar_t__ skb_dma_len; scalar_t__ skb_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 

__attribute__((used)) static void xlgmac_unmap_desc_data(struct xlgmac_pdata *pdata,
				   struct xlgmac_desc_data *desc_data)
{
	if (desc_data->skb_dma) {
		if (desc_data->mapped_as_page) {
			dma_unmap_page(pdata->dev, desc_data->skb_dma,
				       desc_data->skb_dma_len, DMA_TO_DEVICE);
		} else {
			dma_unmap_single(pdata->dev, desc_data->skb_dma,
					 desc_data->skb_dma_len, DMA_TO_DEVICE);
		}
		desc_data->skb_dma = 0;
		desc_data->skb_dma_len = 0;
	}

	if (desc_data->skb) {
		dev_kfree_skb_any(desc_data->skb);
		desc_data->skb = NULL;
	}

	if (desc_data->rx.hdr.pa.pages)
		put_page(desc_data->rx.hdr.pa.pages);

	if (desc_data->rx.hdr.pa_unmap.pages) {
		dma_unmap_page(pdata->dev, desc_data->rx.hdr.pa_unmap.pages_dma,
			       desc_data->rx.hdr.pa_unmap.pages_len,
			       DMA_FROM_DEVICE);
		put_page(desc_data->rx.hdr.pa_unmap.pages);
	}

	if (desc_data->rx.buf.pa.pages)
		put_page(desc_data->rx.buf.pa.pages);

	if (desc_data->rx.buf.pa_unmap.pages) {
		dma_unmap_page(pdata->dev, desc_data->rx.buf.pa_unmap.pages_dma,
			       desc_data->rx.buf.pa_unmap.pages_len,
			       DMA_FROM_DEVICE);
		put_page(desc_data->rx.buf.pa_unmap.pages);
	}

	memset(&desc_data->tx, 0, sizeof(desc_data->tx));
	memset(&desc_data->rx, 0, sizeof(desc_data->rx));

	desc_data->mapped_as_page = 0;

	if (desc_data->state_saved) {
		desc_data->state_saved = 0;
		desc_data->state.skb = NULL;
		desc_data->state.len = 0;
		desc_data->state.error = 0;
	}
}