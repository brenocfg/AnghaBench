#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hal2_desc {int dummy; } ;
struct hal2_codec {int desc_count; int /*<<< orphan*/  buffer_dma; int /*<<< orphan*/  buffer; int /*<<< orphan*/  desc_dma; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NON_CONSISTENT ; 
 int H2_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hal2_free_dmabuf(struct hal2_codec *codec)
{
	dma_free_attrs(NULL, codec->desc_count * sizeof(struct hal2_desc),
		       codec->desc, codec->desc_dma, DMA_ATTR_NON_CONSISTENT);
	dma_free_attrs(NULL, H2_BUF_SIZE, codec->buffer, codec->buffer_dma,
		       DMA_ATTR_NON_CONSISTENT);
}