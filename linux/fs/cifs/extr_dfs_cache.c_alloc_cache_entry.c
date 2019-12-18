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
struct dfs_info3_param {int dummy; } ;
struct dfs_cache_entry {int /*<<< orphan*/  ce_path; int /*<<< orphan*/  ce_tlist; int /*<<< orphan*/  ce_hlist; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dfs_cache_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int copy_ref_data (struct dfs_info3_param const*,int,struct dfs_cache_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfs_cache_slab ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dfs_cache_entry*) ; 
 struct dfs_cache_entry* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dfs_cache_entry *
alloc_cache_entry(const char *path, const struct dfs_info3_param *refs,
		  int numrefs)
{
	struct dfs_cache_entry *ce;
	int rc;

	ce = kmem_cache_zalloc(dfs_cache_slab, GFP_KERNEL);
	if (!ce)
		return ERR_PTR(-ENOMEM);

	ce->ce_path = kstrdup_const(path, GFP_KERNEL);
	if (!ce->ce_path) {
		kmem_cache_free(dfs_cache_slab, ce);
		return ERR_PTR(-ENOMEM);
	}
	INIT_HLIST_NODE(&ce->ce_hlist);
	INIT_LIST_HEAD(&ce->ce_tlist);

	rc = copy_ref_data(refs, numrefs, ce, NULL);
	if (rc) {
		kfree_const(ce->ce_path);
		kmem_cache_free(dfs_cache_slab, ce);
		ce = ERR_PTR(rc);
	}
	return ce;
}