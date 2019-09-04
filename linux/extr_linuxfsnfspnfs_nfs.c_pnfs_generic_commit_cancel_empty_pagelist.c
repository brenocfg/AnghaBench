#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_commit_info {TYPE_1__* mds; } ;
struct nfs_commit_data {int /*<<< orphan*/  context; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rpcs_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  nfs_commit_free (struct nfs_commit_data*) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
pnfs_generic_commit_cancel_empty_pagelist(struct list_head *pages,
					  struct nfs_commit_data *data,
					  struct nfs_commit_info *cinfo)
{
	if (list_empty(pages)) {
		if (atomic_dec_and_test(&cinfo->mds->rpcs_out))
			wake_up_var(&cinfo->mds->rpcs_out);
		/* don't call nfs_commitdata_release - it tries to put
		 * the open_context which is not acquired until nfs_init_commit
		 * which has not been called on @data */
		WARN_ON_ONCE(data->context);
		nfs_commit_free(data);
		return true;
	}

	return false;
}