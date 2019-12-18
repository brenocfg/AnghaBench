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
struct fscrypt_ctx {int /*<<< orphan*/  free_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int FS_CFLG_OWN_PAGES ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ fscrypt_bounce_page_pool ; 
 int /*<<< orphan*/  fscrypt_ctx_cachep ; 
 int /*<<< orphan*/  fscrypt_destroy () ; 
 int /*<<< orphan*/  fscrypt_free_ctxs ; 
 int /*<<< orphan*/  fscrypt_init_mutex ; 
 struct fscrypt_ctx* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mempool_create_page_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_prealloc_crypto_ctxs ; 
 int /*<<< orphan*/  num_prealloc_crypto_pages ; 

int fscrypt_initialize(unsigned int cop_flags)
{
	int i, res = -ENOMEM;

	/* No need to allocate a bounce page pool if this FS won't use it. */
	if (cop_flags & FS_CFLG_OWN_PAGES)
		return 0;

	mutex_lock(&fscrypt_init_mutex);
	if (fscrypt_bounce_page_pool)
		goto already_initialized;

	for (i = 0; i < num_prealloc_crypto_ctxs; i++) {
		struct fscrypt_ctx *ctx;

		ctx = kmem_cache_zalloc(fscrypt_ctx_cachep, GFP_NOFS);
		if (!ctx)
			goto fail;
		list_add(&ctx->free_list, &fscrypt_free_ctxs);
	}

	fscrypt_bounce_page_pool =
		mempool_create_page_pool(num_prealloc_crypto_pages, 0);
	if (!fscrypt_bounce_page_pool)
		goto fail;

already_initialized:
	mutex_unlock(&fscrypt_init_mutex);
	return 0;
fail:
	fscrypt_destroy();
	mutex_unlock(&fscrypt_init_mutex);
	return res;
}