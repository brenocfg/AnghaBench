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
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ncommit; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_CLEAN ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_list_add_request (struct nfs_page*,struct list_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nfs_request_add_commit_list_locked(struct nfs_page *req, struct list_head *dst,
			    struct nfs_commit_info *cinfo)
{
	set_bit(PG_CLEAN, &req->wb_flags);
	nfs_list_add_request(req, dst);
	atomic_long_inc(&cinfo->mds->ncommit);
}