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
struct voctrl_performance_data {int dummy; } ;
struct render_backend {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  renderer; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_perfdata (int /*<<< orphan*/ ,struct voctrl_performance_data*) ; 

__attribute__((used)) static void perfdata(struct render_backend *ctx,
                     struct voctrl_performance_data *out)
{
    struct priv *p = ctx->priv;

    gl_video_perfdata(p->renderer, out);
}