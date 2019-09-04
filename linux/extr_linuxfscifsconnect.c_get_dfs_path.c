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
struct nls_table {int dummy; } ;
struct dfs_info3_param {int dummy; } ;
struct cifs_ses {TYPE_2__* server; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_dfs_refer ) (unsigned int const,struct cifs_ses*,char const*,struct dfs_info3_param**,unsigned int*,struct nls_table const*,int) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (unsigned int const,struct cifs_ses*,char const*,struct dfs_info3_param**,unsigned int*,struct nls_table const*,int) ; 

int
get_dfs_path(const unsigned int xid, struct cifs_ses *ses, const char *old_path,
	     const struct nls_table *nls_codepage, unsigned int *num_referrals,
	     struct dfs_info3_param **referrals, int remap)
{
	int rc = 0;

	if (!ses->server->ops->get_dfs_refer)
		return -ENOSYS;

	*num_referrals = 0;
	*referrals = NULL;

	rc = ses->server->ops->get_dfs_refer(xid, ses, old_path,
					     referrals, num_referrals,
					     nls_codepage, remap);
	return rc;
}