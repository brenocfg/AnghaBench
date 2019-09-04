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
typedef  size_t u64 ;
struct sg_table {size_t size; int nents; int /*<<< orphan*/  sgl; } ;
struct dma_buf_attachment {size_t size; int nents; int /*<<< orphan*/  sgl; } ;
struct dma_buf {size_t size; int nents; int /*<<< orphan*/  sgl; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PTR_ERR (struct sg_table*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sg_table* dma_buf_attach (struct sg_table*,struct device*) ; 
 int /*<<< orphan*/  dma_buf_detach (struct sg_table*,struct sg_table*) ; 
 struct sg_table* dma_buf_get (int) ; 
 struct sg_table* dma_buf_map_attachment (struct sg_table*,int) ; 
 int /*<<< orphan*/  dma_buf_put (struct sg_table*) ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (struct sg_table*,struct sg_table*,int) ; 
 scalar_t__ sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_vde_attach_dmabuf(struct device *dev,
				   int fd,
				   unsigned long offset,
				   size_t min_size,
				   size_t align_size,
				   struct dma_buf_attachment **a,
				   dma_addr_t *addr,
				   struct sg_table **s,
				   size_t *size,
				   enum dma_data_direction dma_dir)
{
	struct dma_buf_attachment *attachment;
	struct dma_buf *dmabuf;
	struct sg_table *sgt;
	int err;

	dmabuf = dma_buf_get(fd);
	if (IS_ERR(dmabuf)) {
		dev_err(dev, "Invalid dmabuf FD\n");
		return PTR_ERR(dmabuf);
	}

	if (dmabuf->size & (align_size - 1)) {
		dev_err(dev, "Unaligned dmabuf 0x%zX, should be aligned to 0x%zX\n",
			dmabuf->size, align_size);
		return -EINVAL;
	}

	if ((u64)offset + min_size > dmabuf->size) {
		dev_err(dev, "Too small dmabuf size %zu @0x%lX, should be at least %zu\n",
			dmabuf->size, offset, min_size);
		return -EINVAL;
	}

	attachment = dma_buf_attach(dmabuf, dev);
	if (IS_ERR(attachment)) {
		dev_err(dev, "Failed to attach dmabuf\n");
		err = PTR_ERR(attachment);
		goto err_put;
	}

	sgt = dma_buf_map_attachment(attachment, dma_dir);
	if (IS_ERR(sgt)) {
		dev_err(dev, "Failed to get dmabufs sg_table\n");
		err = PTR_ERR(sgt);
		goto err_detach;
	}

	if (sgt->nents != 1) {
		dev_err(dev, "Sparse DMA region is unsupported\n");
		err = -EINVAL;
		goto err_unmap;
	}

	*addr = sg_dma_address(sgt->sgl) + offset;
	*a = attachment;
	*s = sgt;

	if (size)
		*size = dmabuf->size - offset;

	return 0;

err_unmap:
	dma_buf_unmap_attachment(attachment, sgt, dma_dir);
err_detach:
	dma_buf_detach(dmabuf, attachment);
err_put:
	dma_buf_put(dmabuf);

	return err;
}