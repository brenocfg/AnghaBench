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
struct TYPE_2__ {int /*<<< orphan*/  pages; void* addr; } ;
struct xenbus_map_node {unsigned int nr_handles; TYPE_1__ hvm; int /*<<< orphan*/  handles; int /*<<< orphan*/  next; } ;
struct xenbus_device {int dummy; } ;
struct map_ring_valloc_hvm {int /*<<< orphan*/  addrs; int /*<<< orphan*/  phys_addrs; int /*<<< orphan*/  idx; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int VM_IOREMAP ; 
 int VM_MAP ; 
 unsigned int XENBUS_MAX_RING_GRANTS ; 
 unsigned int XENBUS_PAGES (unsigned int) ; 
 int __xenbus_map_ring (struct xenbus_device*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int alloc_xenballooned_pages (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xenballooned_pages (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_foreach_grant (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct map_ring_valloc_hvm*) ; 
 int /*<<< orphan*/  kfree (struct xenbus_map_node*) ; 
 struct xenbus_map_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_alert (char*,void*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* vmap (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_map_ring_setup_grant_hvm ; 
 int /*<<< orphan*/  xenbus_unmap_ring (struct xenbus_device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_valloc_lock ; 
 int /*<<< orphan*/  xenbus_valloc_pages ; 

__attribute__((used)) static int xenbus_map_ring_valloc_hvm(struct xenbus_device *dev,
				      grant_ref_t *gnt_ref,
				      unsigned int nr_grefs,
				      void **vaddr)
{
	struct xenbus_map_node *node;
	int err;
	void *addr;
	bool leaked = false;
	struct map_ring_valloc_hvm info = {
		.idx = 0,
	};
	unsigned int nr_pages = XENBUS_PAGES(nr_grefs);

	if (nr_grefs > XENBUS_MAX_RING_GRANTS)
		return -EINVAL;

	*vaddr = NULL;

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	err = alloc_xenballooned_pages(nr_pages, node->hvm.pages);
	if (err)
		goto out_err;

	gnttab_foreach_grant(node->hvm.pages, nr_grefs,
			     xenbus_map_ring_setup_grant_hvm,
			     &info);

	err = __xenbus_map_ring(dev, gnt_ref, nr_grefs, node->handles,
				info.phys_addrs, GNTMAP_host_map, &leaked);
	node->nr_handles = nr_grefs;

	if (err)
		goto out_free_ballooned_pages;

	addr = vmap(node->hvm.pages, nr_pages, VM_MAP | VM_IOREMAP,
		    PAGE_KERNEL);
	if (!addr) {
		err = -ENOMEM;
		goto out_xenbus_unmap_ring;
	}

	node->hvm.addr = addr;

	spin_lock(&xenbus_valloc_lock);
	list_add(&node->next, &xenbus_valloc_pages);
	spin_unlock(&xenbus_valloc_lock);

	*vaddr = addr;
	return 0;

 out_xenbus_unmap_ring:
	if (!leaked)
		xenbus_unmap_ring(dev, node->handles, nr_grefs, info.addrs);
	else
		pr_alert("leaking %p size %u page(s)",
			 addr, nr_pages);
 out_free_ballooned_pages:
	if (!leaked)
		free_xenballooned_pages(nr_pages, node->hvm.pages);
 out_err:
	kfree(node);
	return err;
}