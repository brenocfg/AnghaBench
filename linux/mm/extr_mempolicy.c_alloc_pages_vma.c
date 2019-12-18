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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int preferred_node; } ;
struct mempolicy {scalar_t__ mode; int flags; TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TRANSPARENT_HUGEPAGE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MPOL_F_LOCAL ; 
 scalar_t__ MPOL_INTERLEAVE ; 
 scalar_t__ MPOL_PREFERRED ; 
 scalar_t__ PAGE_SHIFT ; 
 int __GFP_DIRECT_RECLAIM ; 
 int __GFP_NORETRY ; 
 int __GFP_THISNODE ; 
 struct page* __alloc_pages_node (int,int,int) ; 
 struct page* __alloc_pages_nodemask (int,int,int,int /*<<< orphan*/ *) ; 
 struct page* alloc_page_interleave (int,int,unsigned int) ; 
 struct mempolicy* get_vma_policy (struct vm_area_struct*,unsigned long) ; 
 unsigned int interleave_nid (struct mempolicy*,struct vm_area_struct*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  mpol_cond_put (struct mempolicy*) ; 
 scalar_t__ node_isset (int,int /*<<< orphan*/ ) ; 
 int policy_node (int,struct mempolicy*,int) ; 
 int /*<<< orphan*/ * policy_nodemask (int,struct mempolicy*) ; 
 scalar_t__ unlikely (int) ; 

struct page *
alloc_pages_vma(gfp_t gfp, int order, struct vm_area_struct *vma,
		unsigned long addr, int node, bool hugepage)
{
	struct mempolicy *pol;
	struct page *page;
	int preferred_nid;
	nodemask_t *nmask;

	pol = get_vma_policy(vma, addr);

	if (pol->mode == MPOL_INTERLEAVE) {
		unsigned nid;

		nid = interleave_nid(pol, vma, addr, PAGE_SHIFT + order);
		mpol_cond_put(pol);
		page = alloc_page_interleave(gfp, order, nid);
		goto out;
	}

	if (unlikely(IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE) && hugepage)) {
		int hpage_node = node;

		/*
		 * For hugepage allocation and non-interleave policy which
		 * allows the current node (or other explicitly preferred
		 * node) we only try to allocate from the current/preferred
		 * node and don't fall back to other nodes, as the cost of
		 * remote accesses would likely offset THP benefits.
		 *
		 * If the policy is interleave, or does not allow the current
		 * node in its nodemask, we allocate the standard way.
		 */
		if (pol->mode == MPOL_PREFERRED && !(pol->flags & MPOL_F_LOCAL))
			hpage_node = pol->v.preferred_node;

		nmask = policy_nodemask(gfp, pol);
		if (!nmask || node_isset(hpage_node, *nmask)) {
			mpol_cond_put(pol);
			page = __alloc_pages_node(hpage_node,
						gfp | __GFP_THISNODE, order);

			/*
			 * If hugepage allocations are configured to always
			 * synchronous compact or the vma has been madvised
			 * to prefer hugepage backing, retry allowing remote
			 * memory as well.
			 */
			if (!page && (gfp & __GFP_DIRECT_RECLAIM))
				page = __alloc_pages_node(hpage_node,
						gfp | __GFP_NORETRY, order);

			goto out;
		}
	}

	nmask = policy_nodemask(gfp, pol);
	preferred_nid = policy_node(gfp, pol, node);
	page = __alloc_pages_nodemask(gfp, order, preferred_nid, nmask);
	mpol_cond_put(pol);
out:
	return page;
}