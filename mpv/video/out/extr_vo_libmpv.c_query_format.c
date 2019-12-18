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
struct vo_priv {struct mpv_render_context* ctx; } ;
struct vo {struct vo_priv* priv; } ;
struct mpv_render_context {int* imgfmt_supported; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int IMGFMT_END ; 
 int IMGFMT_START ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_format(struct vo *vo, int format)
{
    struct vo_priv *p = vo->priv;
    struct mpv_render_context *ctx = p->ctx;

    bool ok = false;
    pthread_mutex_lock(&ctx->lock);
    if (format >= IMGFMT_START && format < IMGFMT_END)
        ok = ctx->imgfmt_supported[format - IMGFMT_START];
    pthread_mutex_unlock(&ctx->lock);
    return ok;
}