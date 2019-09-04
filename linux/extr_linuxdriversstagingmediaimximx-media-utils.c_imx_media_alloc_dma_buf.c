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
struct imx_media_dma_buf {int /*<<< orphan*/  virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct imx_media_dev {TYPE_1__ md; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  imx_media_free_dma_buf (struct imx_media_dev*,struct imx_media_dma_buf*) ; 

int imx_media_alloc_dma_buf(struct imx_media_dev *imxmd,
			    struct imx_media_dma_buf *buf,
			    int size)
{
	imx_media_free_dma_buf(imxmd, buf);

	buf->len = PAGE_ALIGN(size);
	buf->virt = dma_alloc_coherent(imxmd->md.dev, buf->len, &buf->phys,
				       GFP_DMA | GFP_KERNEL);
	if (!buf->virt) {
		dev_err(imxmd->md.dev, "failed to alloc dma buffer\n");
		return -ENOMEM;
	}

	return 0;
}