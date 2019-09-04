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
struct sg_table {int dummy; } ;
struct dma_buf_attachment {struct dma_buf* dmabuf; } ;
struct dma_buf {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_detach (struct dma_buf*,struct dma_buf_attachment*) ; 
 int /*<<< orphan*/  dma_buf_put (struct dma_buf*) ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (struct dma_buf_attachment*,struct sg_table*,int) ; 

__attribute__((used)) static void tegra_vde_detach_and_put_dmabuf(struct dma_buf_attachment *a,
					    struct sg_table *sgt,
					    enum dma_data_direction dma_dir)
{
	struct dma_buf *dmabuf = a->dmabuf;

	dma_buf_unmap_attachment(a, sgt, dma_dir);
	dma_buf_detach(dmabuf, a);
	dma_buf_put(dmabuf);
}