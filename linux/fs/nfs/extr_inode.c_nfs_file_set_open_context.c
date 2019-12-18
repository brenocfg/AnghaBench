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
struct nfs_open_context {int /*<<< orphan*/  list; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_nfs_open_context (struct nfs_open_context*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_inode_attach_open_context (struct nfs_open_context*) ; 

void nfs_file_set_open_context(struct file *filp, struct nfs_open_context *ctx)
{
	filp->private_data = get_nfs_open_context(ctx);
	if (list_empty(&ctx->list))
		nfs_inode_attach_open_context(ctx);
}