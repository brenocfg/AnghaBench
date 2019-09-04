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
struct imx_media_dma_buf {scalar_t__ phys; int /*<<< orphan*/ * virt; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct imx_media_dev {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void imx_media_free_dma_buf(struct imx_media_dev *imxmd,
			    struct imx_media_dma_buf *buf)
{
	if (buf->virt)
		dma_free_coherent(imxmd->md.dev, buf->len,
				  buf->virt, buf->phys);

	buf->virt = NULL;
	buf->phys = 0;
}