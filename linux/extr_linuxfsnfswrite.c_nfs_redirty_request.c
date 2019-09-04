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
struct nfs_page {TYPE_1__* wb_context; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CONTEXT_RESEND_WRITES ; 
 int /*<<< orphan*/  nfs_end_page_writeback (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_mark_request_dirty (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_redirty_request(struct nfs_page *req)
{
	nfs_mark_request_dirty(req);
	set_bit(NFS_CONTEXT_RESEND_WRITES, &req->wb_context->flags);
	nfs_end_page_writeback(req);
	nfs_release_request(req);
}