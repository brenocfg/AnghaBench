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
struct cifs_tcon {int dummy; } ;

/* Variables and functions */
 int EREMOTE ; 

__attribute__((used)) static int
cifs_unix_dfs_readlink(const unsigned int xid, struct cifs_tcon *tcon,
		       const unsigned char *searchName, char **symlinkinfo,
		       const struct nls_table *nls_codepage)
{
#ifdef CONFIG_CIFS_DFS_UPCALL
	int rc;
	unsigned int num_referrals = 0;
	struct dfs_info3_param *referrals = NULL;

	rc = get_dfs_path(xid, tcon->ses, searchName, nls_codepage,
			  &num_referrals, &referrals, 0);

	if (!rc && num_referrals > 0) {
		*symlinkinfo = kstrndup(referrals->node_name,
					strlen(referrals->node_name),
					GFP_KERNEL);
		if (!*symlinkinfo)
			rc = -ENOMEM;
		free_dfs_info_array(referrals, num_referrals);
	}
	return rc;
#else /* No DFS support */
	return -EREMOTE;
#endif
}