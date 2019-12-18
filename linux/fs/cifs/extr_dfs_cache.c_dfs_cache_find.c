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
struct nls_table {int dummy; } ;
struct dfs_info3_param {int dummy; } ;
struct dfs_cache_tgt_list {int dummy; } ;
struct dfs_cache_entry {int dummy; } ;
struct cifs_ses {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (struct dfs_cache_entry*) ; 
 int PTR_ERR (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  dfs_cache_list_lock ; 
 struct dfs_cache_entry* do_dfs_cache_find (unsigned int const,struct cifs_ses*,struct nls_table const*,int,char*,int) ; 
 int /*<<< orphan*/  free_normalized_path (char const*,char*) ; 
 int get_normalized_path (char const*,char**) ; 
 int get_tgt_list (struct dfs_cache_entry*,struct dfs_cache_tgt_list*) ; 
 int /*<<< orphan*/  get_tgt_name (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  is_path_valid (char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int setup_ref (char const*,struct dfs_cache_entry*,struct dfs_info3_param*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int dfs_cache_find(const unsigned int xid, struct cifs_ses *ses,
		   const struct nls_table *nls_codepage, int remap,
		   const char *path, struct dfs_info3_param *ref,
		   struct dfs_cache_tgt_list *tgt_list)
{
	int rc;
	char *npath;
	struct dfs_cache_entry *ce;

	if (unlikely(!is_path_valid(path)))
		return -EINVAL;

	rc = get_normalized_path(path, &npath);
	if (rc)
		return rc;

	mutex_lock(&dfs_cache_list_lock);
	ce = do_dfs_cache_find(xid, ses, nls_codepage, remap, npath, false);
	if (!IS_ERR(ce)) {
		if (ref)
			rc = setup_ref(path, ce, ref, get_tgt_name(ce));
		else
			rc = 0;
		if (!rc && tgt_list)
			rc = get_tgt_list(ce, tgt_list);
	} else {
		rc = PTR_ERR(ce);
	}
	mutex_unlock(&dfs_cache_list_lock);
	free_normalized_path(path, npath);
	return rc;
}