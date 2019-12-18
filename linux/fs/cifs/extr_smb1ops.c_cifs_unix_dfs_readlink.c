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
struct dfs_info3_param {int /*<<< orphan*/  node_name; int /*<<< orphan*/  member_0; } ;
struct cifs_tcon {int /*<<< orphan*/  ses; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EREMOTE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_dfs_info_param (struct dfs_info3_param*) ; 
 int get_dfs_path (unsigned int const,int /*<<< orphan*/ ,unsigned char const*,struct nls_table const*,struct dfs_info3_param*,int /*<<< orphan*/ ) ; 
 char* kstrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_unix_dfs_readlink(const unsigned int xid, struct cifs_tcon *tcon,
		       const unsigned char *searchName, char **symlinkinfo,
		       const struct nls_table *nls_codepage)
{
#ifdef CONFIG_CIFS_DFS_UPCALL
	int rc;
	struct dfs_info3_param referral = {0};

	rc = get_dfs_path(xid, tcon->ses, searchName, nls_codepage, &referral,
			  0);

	if (!rc) {
		*symlinkinfo = kstrndup(referral.node_name,
					strlen(referral.node_name),
					GFP_KERNEL);
		free_dfs_info_param(&referral);
		if (!*symlinkinfo)
			rc = -ENOMEM;
	}
	return rc;
#else /* No DFS support */
	return -EREMOTE;
#endif
}