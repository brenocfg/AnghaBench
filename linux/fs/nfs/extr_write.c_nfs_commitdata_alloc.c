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
struct nfs_commit_data {int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 int GFP_NOIO ; 
 int GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct nfs_commit_data* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 struct nfs_commit_data* mempool_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct nfs_commit_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_cdata_cachep ; 
 int /*<<< orphan*/  nfs_commit_mempool ; 

struct nfs_commit_data *nfs_commitdata_alloc(bool never_fail)
{
	struct nfs_commit_data *p;

	if (never_fail)
		p = mempool_alloc(nfs_commit_mempool, GFP_NOIO);
	else {
		/* It is OK to do some reclaim, not no safe to wait
		 * for anything to be returned to the pool.
		 * mempool_alloc() cannot handle that particular combination,
		 * so we need two separate attempts.
		 */
		p = mempool_alloc(nfs_commit_mempool, GFP_NOWAIT);
		if (!p)
			p = kmem_cache_alloc(nfs_cdata_cachep, GFP_NOIO |
					     __GFP_NOWARN | __GFP_NORETRY);
		if (!p)
			return NULL;
	}

	memset(p, 0, sizeof(*p));
	INIT_LIST_HEAD(&p->pages);
	return p;
}