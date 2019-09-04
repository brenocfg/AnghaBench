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
struct zbud_header {scalar_t__ under_reclaim; int /*<<< orphan*/  lru; int /*<<< orphan*/  buddy; scalar_t__ last_chunks; scalar_t__ first_chunks; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct zbud_header* page_address (struct page*) ; 

__attribute__((used)) static struct zbud_header *init_zbud_page(struct page *page)
{
	struct zbud_header *zhdr = page_address(page);
	zhdr->first_chunks = 0;
	zhdr->last_chunks = 0;
	INIT_LIST_HEAD(&zhdr->buddy);
	INIT_LIST_HEAD(&zhdr->lru);
	zhdr->under_reclaim = 0;
	return zhdr;
}