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
struct mp_image {int dummy; } ;

/* Variables and functions */
 struct mp_image* gl_video_get_image (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static struct mp_image *get_image(struct render_backend *ctx, int imgfmt,
                                  int w, int h, int stride_align)
{
    struct priv *p = ctx->priv;

    return gl_video_get_image(p->renderer, imgfmt, w, h, stride_align);
}