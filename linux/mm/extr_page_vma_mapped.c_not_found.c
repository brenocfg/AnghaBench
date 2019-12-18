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
struct page_vma_mapped_walk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_vma_mapped_walk_done (struct page_vma_mapped_walk*) ; 

__attribute__((used)) static inline bool not_found(struct page_vma_mapped_walk *pvmw)
{
	page_vma_mapped_walk_done(pvmw);
	return false;
}