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
struct nfs_page {int /*<<< orphan*/  wb_flags; } ;
struct nfs_commit_info {TYPE_1__* mds; } ;
struct TYPE_2__ {int /*<<< orphan*/  ncommit; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_CLEAN ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_list_remove_request (struct nfs_page*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nfs_request_remove_commit_list(struct nfs_page *req,
			       struct nfs_commit_info *cinfo)
{
	if (!test_and_clear_bit(PG_CLEAN, &(req)->wb_flags))
		return;
	nfs_list_remove_request(req);
	atomic_long_dec(&cinfo->mds->ncommit);
}