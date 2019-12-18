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
struct zbud_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/ * unbuddied; int /*<<< orphan*/  pages_nr; } ;
struct zbud_header {scalar_t__ last_chunks; scalar_t__ first_chunks; int /*<<< orphan*/  buddy; int /*<<< orphan*/  lru; scalar_t__ under_reclaim; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long ZHDR_SIZE_ALIGNED ; 
 int /*<<< orphan*/  free_zbud_page (struct zbud_header*) ; 
 struct zbud_header* handle_to_zbud_header (unsigned long) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int num_free_chunks (struct zbud_header*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void zbud_free(struct zbud_pool *pool, unsigned long handle)
{
	struct zbud_header *zhdr;
	int freechunks;

	spin_lock(&pool->lock);
	zhdr = handle_to_zbud_header(handle);

	/* If first buddy, handle will be page aligned */
	if ((handle - ZHDR_SIZE_ALIGNED) & ~PAGE_MASK)
		zhdr->last_chunks = 0;
	else
		zhdr->first_chunks = 0;

	if (zhdr->under_reclaim) {
		/* zbud page is under reclaim, reclaim will free */
		spin_unlock(&pool->lock);
		return;
	}

	/* Remove from existing buddy list */
	list_del(&zhdr->buddy);

	if (zhdr->first_chunks == 0 && zhdr->last_chunks == 0) {
		/* zbud page is empty, free */
		list_del(&zhdr->lru);
		free_zbud_page(zhdr);
		pool->pages_nr--;
	} else {
		/* Add to unbuddied list */
		freechunks = num_free_chunks(zhdr);
		list_add(&zhdr->buddy, &pool->unbuddied[freechunks]);
	}

	spin_unlock(&pool->lock);
}