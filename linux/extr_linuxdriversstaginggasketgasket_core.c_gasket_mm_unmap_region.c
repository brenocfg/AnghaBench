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
typedef  scalar_t__ ulong ;
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct gasket_mappable_region {scalar_t__ length_bytes; } ;
struct gasket_dev {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  gasket_mm_get_mapping_addrs (struct gasket_mappable_region const*,scalar_t__,scalar_t__,struct gasket_mappable_region*,scalar_t__*) ; 
 int gasket_mm_vma_bar_offset (struct gasket_dev const*,struct vm_area_struct*,scalar_t__*) ; 
 int /*<<< orphan*/  zap_vma_ptes (struct vm_area_struct*,scalar_t__,int) ; 

int gasket_mm_unmap_region(const struct gasket_dev *gasket_dev,
			   struct vm_area_struct *vma,
			   const struct gasket_mappable_region *map_region)
{
	ulong bar_offset;
	ulong virt_offset;
	struct gasket_mappable_region mappable_region;
	int ret;

	if (map_region->length_bytes == 0)
		return 0;

	ret = gasket_mm_vma_bar_offset(gasket_dev, vma, &bar_offset);
	if (ret)
		return ret;

	if (!gasket_mm_get_mapping_addrs(map_region, bar_offset,
					 vma->vm_end - vma->vm_start,
					 &mappable_region, &virt_offset))
		return 1;

	/*
	 * The length passed to zap_vma_ptes MUST BE A MULTIPLE OF
	 * PAGE_SIZE! Trust me. I have the scars.
	 *
	 * Next multiple of y: ceil_div(x, y) * y
	 */
	zap_vma_ptes(vma, vma->vm_start + virt_offset,
		     DIV_ROUND_UP(mappable_region.length_bytes, PAGE_SIZE) *
		     PAGE_SIZE);
	return 0;
}