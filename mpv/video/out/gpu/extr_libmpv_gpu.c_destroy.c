#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct render_backend {int /*<<< orphan*/  hwdec_devs; struct priv* priv; } ;
struct priv {TYPE_2__* context; scalar_t__ renderer; } ;
struct TYPE_5__ {struct TYPE_5__* priv; TYPE_1__* fns; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_uninit (scalar_t__) ; 
 int /*<<< orphan*/  hwdec_devices_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  talloc_free (TYPE_2__*) ; 

__attribute__((used)) static void destroy(struct render_backend *ctx)
{
    struct priv *p = ctx->priv;

    if (p->renderer)
        gl_video_uninit(p->renderer);

    hwdec_devices_destroy(ctx->hwdec_devs);

    if (p->context) {
        p->context->fns->destroy(p->context);
        talloc_free(p->context->priv);
        talloc_free(p->context);
    }
}