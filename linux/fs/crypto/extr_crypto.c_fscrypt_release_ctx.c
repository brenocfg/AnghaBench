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
struct fscrypt_ctx {int flags; int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int FS_CTX_REQUIRES_FREE_ENCRYPT_FL ; 
 int /*<<< orphan*/  fscrypt_ctx_cachep ; 
 int /*<<< orphan*/  fscrypt_ctx_lock ; 
 int /*<<< orphan*/  fscrypt_free_ctxs ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fscrypt_ctx*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void fscrypt_release_ctx(struct fscrypt_ctx *ctx)
{
	unsigned long flags;

	if (ctx->flags & FS_CTX_REQUIRES_FREE_ENCRYPT_FL) {
		kmem_cache_free(fscrypt_ctx_cachep, ctx);
	} else {
		spin_lock_irqsave(&fscrypt_ctx_lock, flags);
		list_add(&ctx->free_list, &fscrypt_free_ctxs);
		spin_unlock_irqrestore(&fscrypt_ctx_lock, flags);
	}
}