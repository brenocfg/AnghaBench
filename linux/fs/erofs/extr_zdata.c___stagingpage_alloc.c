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
struct page {int /*<<< orphan*/  mapping; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  Z_EROFS_MAPPING_STAGING ; 
 struct page* erofs_allocpage (struct list_head*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct page *__stagingpage_alloc(struct list_head *pagepool,
					       gfp_t gfp)
{
	struct page *page = erofs_allocpage(pagepool, gfp, true);

	page->mapping = Z_EROFS_MAPPING_STAGING;
	return page;
}