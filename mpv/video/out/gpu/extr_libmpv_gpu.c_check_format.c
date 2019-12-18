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

/* Variables and functions */
 int gl_video_check_format (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool check_format(struct render_backend *ctx, int imgfmt)
{
    struct priv *p = ctx->priv;

    return gl_video_check_format(p->renderer, imgfmt);
}