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
struct nfs_page {int /*<<< orphan*/  wb_nio; int /*<<< orphan*/  wb_index; int /*<<< orphan*/  wb_page; int /*<<< orphan*/  wb_lock_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct nfs_page*) ; 
 struct nfs_page* __nfs_create_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nfs_lock_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_page_group_init (struct nfs_page*,struct nfs_page*) ; 

__attribute__((used)) static struct nfs_page *
nfs_create_subreq(struct nfs_page *req, struct nfs_page *last,
		  unsigned int pgbase, unsigned int offset,
		  unsigned int count)
{
	struct nfs_page *ret;

	ret = __nfs_create_request(req->wb_lock_context, req->wb_page,
			pgbase, offset, count);
	if (!IS_ERR(ret)) {
		nfs_lock_request(ret);
		ret->wb_index = req->wb_index;
		nfs_page_group_init(ret, last);
		ret->wb_nio = req->wb_nio;
	}
	return ret;
}