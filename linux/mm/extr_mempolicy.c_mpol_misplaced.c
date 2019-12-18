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
struct zoneref {int /*<<< orphan*/  zone; } ;
struct vm_area_struct {unsigned long vm_pgoff; int /*<<< orphan*/  vm_start; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int preferred_node; int /*<<< orphan*/  nodes; } ;
struct mempolicy {int flags; int mode; TYPE_1__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFP_HIGHUSER ; 
#define  MPOL_BIND 130 
 int MPOL_F_LOCAL ; 
 int MPOL_F_MOF ; 
 int MPOL_F_MORON ; 
#define  MPOL_INTERLEAVE 129 
#define  MPOL_PREFERRED 128 
 int NUMA_NO_NODE ; 
 unsigned long PAGE_SHIFT ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  current ; 
 struct zoneref* first_zones_zonelist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mempolicy* get_vma_policy (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  gfp_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_cond_put (struct mempolicy*) ; 
 int /*<<< orphan*/  node_isset (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_zonelist (int,int /*<<< orphan*/ ) ; 
 int numa_node_id () ; 
 int offset_il_node (struct mempolicy*,unsigned long) ; 
 int page_to_nid (struct page*) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  should_numa_migrate_memory (int /*<<< orphan*/ ,struct page*,int,int) ; 
 int zone_to_nid (int /*<<< orphan*/ ) ; 

int mpol_misplaced(struct page *page, struct vm_area_struct *vma, unsigned long addr)
{
	struct mempolicy *pol;
	struct zoneref *z;
	int curnid = page_to_nid(page);
	unsigned long pgoff;
	int thiscpu = raw_smp_processor_id();
	int thisnid = cpu_to_node(thiscpu);
	int polnid = NUMA_NO_NODE;
	int ret = -1;

	pol = get_vma_policy(vma, addr);
	if (!(pol->flags & MPOL_F_MOF))
		goto out;

	switch (pol->mode) {
	case MPOL_INTERLEAVE:
		pgoff = vma->vm_pgoff;
		pgoff += (addr - vma->vm_start) >> PAGE_SHIFT;
		polnid = offset_il_node(pol, pgoff);
		break;

	case MPOL_PREFERRED:
		if (pol->flags & MPOL_F_LOCAL)
			polnid = numa_node_id();
		else
			polnid = pol->v.preferred_node;
		break;

	case MPOL_BIND:

		/*
		 * allows binding to multiple nodes.
		 * use current page if in policy nodemask,
		 * else select nearest allowed node, if any.
		 * If no allowed nodes, use current [!misplaced].
		 */
		if (node_isset(curnid, pol->v.nodes))
			goto out;
		z = first_zones_zonelist(
				node_zonelist(numa_node_id(), GFP_HIGHUSER),
				gfp_zone(GFP_HIGHUSER),
				&pol->v.nodes);
		polnid = zone_to_nid(z->zone);
		break;

	default:
		BUG();
	}

	/* Migrate the page towards the node whose CPU is referencing it */
	if (pol->flags & MPOL_F_MORON) {
		polnid = thisnid;

		if (!should_numa_migrate_memory(current, page, curnid, thiscpu))
			goto out;
	}

	if (curnid != polnid)
		ret = polnid;
out:
	mpol_cond_put(pol);

	return ret;
}