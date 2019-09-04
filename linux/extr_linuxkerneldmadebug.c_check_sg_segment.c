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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void check_sg_segment(struct device *dev, struct scatterlist *sg)
{
#ifdef CONFIG_DMA_API_DEBUG_SG
	unsigned int max_seg = dma_get_max_seg_size(dev);
	u64 start, end, boundary = dma_get_seg_boundary(dev);

	/*
	 * Either the driver forgot to set dma_parms appropriately, or
	 * whoever generated the list forgot to check them.
	 */
	if (sg->length > max_seg)
		err_printk(dev, NULL, "DMA-API: mapping sg segment longer than device claims to support [len=%u] [max=%u]\n",
			   sg->length, max_seg);
	/*
	 * In some cases this could potentially be the DMA API
	 * implementation's fault, but it would usually imply that
	 * the scatterlist was built inappropriately to begin with.
	 */
	start = sg_dma_address(sg);
	end = start + sg_dma_len(sg) - 1;
	if ((start ^ end) & ~boundary)
		err_printk(dev, NULL, "DMA-API: mapping sg segment across boundary [start=0x%016llx] [end=0x%016llx] [boundary=0x%016llx]\n",
			   start, end, boundary);
#endif
}