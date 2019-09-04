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
struct page {int dummy; } ;
struct TYPE_2__ {struct page* bounce_page; } ;
struct fscrypt_ctx {TYPE_1__ w; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct page* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_CTX_HAS_BOUNCE_BUFFER_FL ; 
 int /*<<< orphan*/  fscrypt_bounce_page_pool ; 
 struct page* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct page *fscrypt_alloc_bounce_page(struct fscrypt_ctx *ctx,
				       gfp_t gfp_flags)
{
	ctx->w.bounce_page = mempool_alloc(fscrypt_bounce_page_pool, gfp_flags);
	if (ctx->w.bounce_page == NULL)
		return ERR_PTR(-ENOMEM);
	ctx->flags |= FS_CTX_HAS_BOUNCE_BUFFER_FL;
	return ctx->w.bounce_page;
}