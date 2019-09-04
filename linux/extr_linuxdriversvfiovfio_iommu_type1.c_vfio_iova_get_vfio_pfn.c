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
struct vfio_pfn {int /*<<< orphan*/  ref_count; } ;
struct vfio_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct vfio_pfn* vfio_find_vpfn (struct vfio_dma*,unsigned long) ; 

__attribute__((used)) static struct vfio_pfn *vfio_iova_get_vfio_pfn(struct vfio_dma *dma,
					       unsigned long iova)
{
	struct vfio_pfn *vpfn = vfio_find_vpfn(dma, iova);

	if (vpfn)
		atomic_inc(&vpfn->ref_count);
	return vpfn;
}