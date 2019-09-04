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
struct render_backend {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  renderer; } ;
struct mp_image_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_config (int /*<<< orphan*/ ,struct mp_image_params*) ; 

__attribute__((used)) static void reconfig(struct render_backend *ctx, struct mp_image_params *params)
{
    struct priv *p = ctx->priv;

    gl_video_config(p->renderer, params);
}