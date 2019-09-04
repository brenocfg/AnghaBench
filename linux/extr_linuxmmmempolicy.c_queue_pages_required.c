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
struct queue_pages {unsigned long flags; int /*<<< orphan*/ * nmask; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned long MPOL_MF_INVERT ; 
 int node_isset (int,int /*<<< orphan*/ ) ; 
 int page_to_nid (struct page*) ; 

__attribute__((used)) static inline bool queue_pages_required(struct page *page,
					struct queue_pages *qp)
{
	int nid = page_to_nid(page);
	unsigned long flags = qp->flags;

	return node_isset(nid, *qp->nmask) == !(flags & MPOL_MF_INVERT);
}