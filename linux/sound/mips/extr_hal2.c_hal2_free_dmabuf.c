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
struct snd_hal2 {TYPE_1__* card; } ;
struct hal2_desc {int dummy; } ;
struct hal2_codec {int desc_count; int /*<<< orphan*/  buffer_dma; int /*<<< orphan*/  buffer; int /*<<< orphan*/  desc_dma; int /*<<< orphan*/  desc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NON_CONSISTENT ; 
 int H2_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hal2_free_dmabuf(struct snd_hal2 *hal2, struct hal2_codec *codec)
{
	struct device *dev = hal2->card->dev;

	dma_free_attrs(dev, codec->desc_count * sizeof(struct hal2_desc),
		       codec->desc, codec->desc_dma, DMA_ATTR_NON_CONSISTENT);
	dma_free_attrs(dev, H2_BUF_SIZE, codec->buffer, codec->buffer_dma,
		       DMA_ATTR_NON_CONSISTENT);
}