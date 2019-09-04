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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static
void nfs_readdir_free_pages(struct page **pages, unsigned int npages)
{
	unsigned int i;
	for (i = 0; i < npages; i++)
		put_page(pages[i]);
}