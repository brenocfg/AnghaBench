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
struct xen_remove_from_physmap {scalar_t__ gpfn; int /*<<< orphan*/  domid; } ;
struct resource {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 int HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_remove_from_physmap*) ; 
 scalar_t__ IORESOURCE_MEM ; 
 int /*<<< orphan*/  XENMEM_remove_from_physmap ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 scalar_t__ XEN_PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource const*) ; 
 scalar_t__ resource_type (struct resource const*) ; 

__attribute__((used)) static int xen_unmap_device_mmio(const struct resource *resources,
				 unsigned int count)
{
	unsigned int i, j, nr;
	int rc = 0;
	const struct resource *r;
	struct xen_remove_from_physmap xrp;

	for (i = 0; i < count; i++) {
		r = &resources[i];
		nr = DIV_ROUND_UP(resource_size(r), XEN_PAGE_SIZE);
		if ((resource_type(r) != IORESOURCE_MEM) || (nr == 0))
			continue;

		for (j = 0; j < nr; j++) {
			xrp.domid = DOMID_SELF;
			xrp.gpfn = XEN_PFN_DOWN(r->start) + j;
			rc = HYPERVISOR_memory_op(XENMEM_remove_from_physmap,
						  &xrp);
			if (rc)
				return rc;
		}
	}

	return rc;
}