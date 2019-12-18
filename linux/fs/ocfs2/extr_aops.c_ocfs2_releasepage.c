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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int try_to_free_buffers (struct page*) ; 

__attribute__((used)) static int ocfs2_releasepage(struct page *page, gfp_t wait)
{
	if (!page_has_buffers(page))
		return 0;
	return try_to_free_buffers(page);
}