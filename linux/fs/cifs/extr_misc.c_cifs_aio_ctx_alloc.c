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
struct cifs_aio_ctx {int /*<<< orphan*/  refcount; int /*<<< orphan*/  done; int /*<<< orphan*/  aio_mutex; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct cifs_aio_ctx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct cifs_aio_ctx *
cifs_aio_ctx_alloc(void)
{
	struct cifs_aio_ctx *ctx;

	/*
	 * Must use kzalloc to initialize ctx->bv to NULL and ctx->direct_io
	 * to false so that we know when we have to unreference pages within
	 * cifs_aio_ctx_release()
	 */
	ctx = kzalloc(sizeof(struct cifs_aio_ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	INIT_LIST_HEAD(&ctx->list);
	mutex_init(&ctx->aio_mutex);
	init_completion(&ctx->done);
	kref_init(&ctx->refcount);
	return ctx;
}