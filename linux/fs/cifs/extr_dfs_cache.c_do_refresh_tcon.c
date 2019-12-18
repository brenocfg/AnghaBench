#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dfs_info3_param {int dummy; } ;
struct dfs_cache_vol_info {int dummy; } ;
struct dfs_cache_entry {TYPE_2__* server; } ;
struct dfs_cache {int /*<<< orphan*/  dc_nlsc; } ;
struct cifs_tcon {char* dfs_path; int /*<<< orphan*/  remap; struct dfs_cache_entry* ses; } ;
struct cifs_ses {TYPE_2__* server; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_dfs_refer ) (unsigned int,struct dfs_cache_entry*,char*,struct dfs_info3_param**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct dfs_cache_entry*) ; 
 int PTR_ERR (struct dfs_cache_entry*) ; 
 struct dfs_cache_entry* __update_cache_entry (char*,struct dfs_info3_param*,int) ; 
 int /*<<< orphan*/  cache_entry_expired (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  cifs_put_smb_ses (struct dfs_cache_entry*) ; 
 int /*<<< orphan*/  dfs_cache_list_lock ; 
 int /*<<< orphan*/  dump_refs (struct dfs_info3_param*,int) ; 
 struct dfs_cache_entry* find_cache_entry (char*,unsigned int*) ; 
 struct dfs_cache_entry* find_root_ses (struct dfs_cache_vol_info*,struct cifs_tcon*,char*) ; 
 int /*<<< orphan*/  free_dfs_info_array (struct dfs_info3_param*,int) ; 
 int /*<<< orphan*/  free_normalized_path (char*,char*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 int get_normalized_path (char*,char**) ; 
 unsigned int get_xid () ; 
 scalar_t__ is_dfs_link (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (unsigned int,struct dfs_cache_entry*,char*,struct dfs_info3_param**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_refresh_tcon(struct dfs_cache *dc, struct dfs_cache_vol_info *vi,
			    struct cifs_tcon *tcon)
{
	int rc = 0;
	unsigned int xid;
	char *path, *npath;
	unsigned int h;
	struct dfs_cache_entry *ce;
	struct dfs_info3_param *refs = NULL;
	int numrefs = 0;
	struct cifs_ses *root_ses = NULL, *ses;

	xid = get_xid();

	path = tcon->dfs_path + 1;

	rc = get_normalized_path(path, &npath);
	if (rc)
		goto out;

	mutex_lock(&dfs_cache_list_lock);
	ce = find_cache_entry(npath, &h);
	mutex_unlock(&dfs_cache_list_lock);

	if (IS_ERR(ce)) {
		rc = PTR_ERR(ce);
		goto out;
	}

	if (!cache_entry_expired(ce))
		goto out;

	/* If it's a DFS Link, then use root SMB session for refreshing it */
	if (is_dfs_link(npath)) {
		ses = root_ses = find_root_ses(vi, tcon, npath);
		if (IS_ERR(ses)) {
			rc = PTR_ERR(ses);
			root_ses = NULL;
			goto out;
		}
	} else {
		ses = tcon->ses;
	}

	if (unlikely(!ses->server->ops->get_dfs_refer)) {
		rc = -EOPNOTSUPP;
	} else {
		rc = ses->server->ops->get_dfs_refer(xid, ses, path, &refs,
						     &numrefs, dc->dc_nlsc,
						     tcon->remap);
		if (!rc) {
			mutex_lock(&dfs_cache_list_lock);
			ce = __update_cache_entry(npath, refs, numrefs);
			mutex_unlock(&dfs_cache_list_lock);
			dump_refs(refs, numrefs);
			free_dfs_info_array(refs, numrefs);
			if (IS_ERR(ce))
				rc = PTR_ERR(ce);
		}
	}

out:
	if (root_ses)
		cifs_put_smb_ses(root_ses);

	free_xid(xid);
	free_normalized_path(path, npath);
}