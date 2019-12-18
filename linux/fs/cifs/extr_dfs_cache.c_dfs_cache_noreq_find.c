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
struct dfs_cache_tgt_list {int dummy; } ;
struct dfs_cache_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dfs_cache_entry*) ; 
 int PTR_ERR (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  dfs_cache_list_lock ; 
 struct dfs_cache_entry* do_dfs_cache_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_normalized_path (char const*,char*) ; 
 int get_normalized_path (char const*,char**) ; 
 int get_tgt_list (struct dfs_cache_entry*,struct dfs_cache_tgt_list*) ; 
 int /*<<< orphan*/  get_tgt_name (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  is_path_valid (char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int setup_ref (char const*,struct dfs_cache_entry*,struct dfs_info3_param*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int dfs_cache_noreq_find(const char *path, struct dfs_info3_param *ref,
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
	ce = do_dfs_cache_find(0, NULL, NULL, 0, npath, true);
	if (IS_ERR(ce)) {
		rc = PTR_ERR(ce);
		goto out;
	}

	if (ref)
		rc = setup_ref(path, ce, ref, get_tgt_name(ce));
	else
		rc = 0;
	if (!rc && tgt_list)
		rc = get_tgt_list(ce, tgt_list);
out:
	mutex_unlock(&dfs_cache_list_lock);
	free_normalized_path(path, npath);
	return rc;
}