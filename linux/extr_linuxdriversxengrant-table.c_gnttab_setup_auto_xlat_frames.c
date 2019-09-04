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
typedef  scalar_t__ xen_pfn_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pfn ;
struct TYPE_2__ {int count; scalar_t__* pfn; void* vaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int XEN_PAGE_SIZE ; 
 scalar_t__ XEN_PFN_DOWN (int /*<<< orphan*/ ) ; 
 unsigned int __max_nr_grant_frames () ; 
 scalar_t__* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ xen_auto_xlat_grant_frames ; 
 void* xen_remap (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xen_unmap (void*) ; 

int gnttab_setup_auto_xlat_frames(phys_addr_t addr)
{
	xen_pfn_t *pfn;
	unsigned int max_nr_gframes = __max_nr_grant_frames();
	unsigned int i;
	void *vaddr;

	if (xen_auto_xlat_grant_frames.count)
		return -EINVAL;

	vaddr = xen_remap(addr, XEN_PAGE_SIZE * max_nr_gframes);
	if (vaddr == NULL) {
		pr_warn("Failed to ioremap gnttab share frames (addr=%pa)!\n",
			&addr);
		return -ENOMEM;
	}
	pfn = kcalloc(max_nr_gframes, sizeof(pfn[0]), GFP_KERNEL);
	if (!pfn) {
		xen_unmap(vaddr);
		return -ENOMEM;
	}
	for (i = 0; i < max_nr_gframes; i++)
		pfn[i] = XEN_PFN_DOWN(addr) + i;

	xen_auto_xlat_grant_frames.vaddr = vaddr;
	xen_auto_xlat_grant_frames.pfn = pfn;
	xen_auto_xlat_grant_frames.count = max_nr_gframes;

	return 0;
}