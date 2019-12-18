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
struct vo_priv {struct mpv_render_context* ctx; } ;
struct vo {int /*<<< orphan*/  hwdec_devs; int /*<<< orphan*/  probing; TYPE_1__* global; struct vo_priv* priv; } ;
struct mpv_render_context {int need_resize; int need_update_external; int /*<<< orphan*/  hwdec_devs; int /*<<< orphan*/  lock; struct vo* vo; } ;
struct TYPE_2__ {int /*<<< orphan*/  client_api; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct vo*,char*) ; 
 int /*<<< orphan*/  VOCTRL_PREINIT ; 
 int /*<<< orphan*/  control (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mpv_render_context* mp_client_api_acquire_render_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    struct vo_priv *p = vo->priv;

    struct mpv_render_context *ctx =
        mp_client_api_acquire_render_context(vo->global->client_api);
    p->ctx = ctx;

    if (!ctx) {
        if (!vo->probing)
            MP_FATAL(vo, "No render context set.\n");
        return -1;
    }

    pthread_mutex_lock(&ctx->lock);
    ctx->vo = vo;
    ctx->need_resize = true;
    ctx->need_update_external = true;
    pthread_mutex_unlock(&ctx->lock);

    vo->hwdec_devs = ctx->hwdec_devs;
    control(vo, VOCTRL_PREINIT, NULL);

    return 0;
}