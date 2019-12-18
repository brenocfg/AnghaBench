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
struct sg_page_iter {scalar_t__ sg_pgoffset; int __pg_advance; scalar_t__ sg; int /*<<< orphan*/  __nents; } ;
struct sg_dma_page_iter {struct sg_page_iter base; } ;

/* Variables and functions */
 scalar_t__ sg_dma_page_count (scalar_t__) ; 
 scalar_t__ sg_next (scalar_t__) ; 

bool __sg_page_iter_dma_next(struct sg_dma_page_iter *dma_iter)
{
	struct sg_page_iter *piter = &dma_iter->base;

	if (!piter->__nents || !piter->sg)
		return false;

	piter->sg_pgoffset += piter->__pg_advance;
	piter->__pg_advance = 1;

	while (piter->sg_pgoffset >= sg_dma_page_count(piter->sg)) {
		piter->sg_pgoffset -= sg_dma_page_count(piter->sg);
		piter->sg = sg_next(piter->sg);
		if (!--piter->__nents || !piter->sg)
			return false;
	}

	return true;
}