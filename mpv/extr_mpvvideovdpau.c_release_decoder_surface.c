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
struct surface_ref {size_t index; struct mp_vdpau_ctx* ctx; } ;
struct mp_vdpau_ctx {int /*<<< orphan*/  pool_lock; TYPE_1__* video_surfaces; } ;
struct TYPE_2__ {int in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct surface_ref*) ; 

__attribute__((used)) static void release_decoder_surface(void *ptr)
{
    struct surface_ref *r = ptr;
    struct mp_vdpau_ctx *ctx = r->ctx;

    pthread_mutex_lock(&ctx->pool_lock);
    assert(ctx->video_surfaces[r->index].in_use);
    ctx->video_surfaces[r->index].in_use = false;
    pthread_mutex_unlock(&ctx->pool_lock);

    talloc_free(r);
}