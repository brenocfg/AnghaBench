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
struct TYPE_2__ {struct nfs_open_context* open_context; } ;
struct nfs_open_context {int /*<<< orphan*/ * mdsthreshold; int /*<<< orphan*/  list; TYPE_1__ lock_context; scalar_t__ flock_owner; scalar_t__ error; scalar_t__ flags; int /*<<< orphan*/  mode; int /*<<< orphan*/ * state; int /*<<< orphan*/ * ll_cred; struct cred const* cred; int /*<<< orphan*/  dentry; } ;
struct file {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;
typedef  scalar_t__ fl_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nfs_open_context* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct cred* get_current_cred () ; 
 struct nfs_open_context* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_lock_context (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_sb_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 

struct nfs_open_context *alloc_nfs_open_context(struct dentry *dentry,
						fmode_t f_mode,
						struct file *filp)
{
	struct nfs_open_context *ctx;
	const struct cred *cred = get_current_cred();

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx) {
		put_cred(cred);
		return ERR_PTR(-ENOMEM);
	}
	nfs_sb_active(dentry->d_sb);
	ctx->dentry = dget(dentry);
	ctx->cred = cred;
	ctx->ll_cred = NULL;
	ctx->state = NULL;
	ctx->mode = f_mode;
	ctx->flags = 0;
	ctx->error = 0;
	ctx->flock_owner = (fl_owner_t)filp;
	nfs_init_lock_context(&ctx->lock_context);
	ctx->lock_context.open_context = ctx;
	INIT_LIST_HEAD(&ctx->list);
	ctx->mdsthreshold = NULL;
	return ctx;
}