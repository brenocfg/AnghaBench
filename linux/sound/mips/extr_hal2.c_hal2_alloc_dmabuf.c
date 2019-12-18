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
struct snd_hal2 {TYPE_1__* card; } ;
struct TYPE_4__ {int cntinfo; void* pnext; void* pbuf; } ;
struct hal2_desc {TYPE_2__ desc; } ;
struct hal2_codec {int desc_count; struct hal2_desc* desc; void* desc_dma; void* buffer_dma; void* buffer; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NON_CONSISTENT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int H2_BLOCK_SIZE ; 
 int H2_BUF_SIZE ; 
 int HPCDMA_XIE ; 
 void* dma_alloc_attrs (struct device*,int,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cache_sync (struct device*,struct hal2_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_attrs (struct device*,int,void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hal2_alloc_dmabuf(struct snd_hal2 *hal2, struct hal2_codec *codec)
{
	struct device *dev = hal2->card->dev;
	struct hal2_desc *desc;
	dma_addr_t desc_dma, buffer_dma;
	int count = H2_BUF_SIZE / H2_BLOCK_SIZE;
	int i;

	codec->buffer = dma_alloc_attrs(dev, H2_BUF_SIZE, &buffer_dma,
					GFP_KERNEL, DMA_ATTR_NON_CONSISTENT);
	if (!codec->buffer)
		return -ENOMEM;
	desc = dma_alloc_attrs(dev, count * sizeof(struct hal2_desc),
			       &desc_dma, GFP_KERNEL, DMA_ATTR_NON_CONSISTENT);
	if (!desc) {
		dma_free_attrs(dev, H2_BUF_SIZE, codec->buffer, buffer_dma,
			       DMA_ATTR_NON_CONSISTENT);
		return -ENOMEM;
	}
	codec->buffer_dma = buffer_dma;
	codec->desc_dma = desc_dma;
	codec->desc = desc;
	for (i = 0; i < count; i++) {
		desc->desc.pbuf = buffer_dma + i * H2_BLOCK_SIZE;
		desc->desc.cntinfo = HPCDMA_XIE | H2_BLOCK_SIZE;
		desc->desc.pnext = (i == count - 1) ?
		      desc_dma : desc_dma + (i + 1) * sizeof(struct hal2_desc);
		desc++;
	}
	dma_cache_sync(dev, codec->desc, count * sizeof(struct hal2_desc),
		       DMA_TO_DEVICE);
	codec->desc_count = count;
	return 0;
}