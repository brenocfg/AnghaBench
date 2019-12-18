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
struct nfs_open_dir_context {int /*<<< orphan*/  cred; int /*<<< orphan*/  list; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs_open_dir_context*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_nfs_open_dir_context(struct inode *dir, struct nfs_open_dir_context *ctx)
{
	spin_lock(&dir->i_lock);
	list_del(&ctx->list);
	spin_unlock(&dir->i_lock);
	put_cred(ctx->cred);
	kfree(ctx);
}