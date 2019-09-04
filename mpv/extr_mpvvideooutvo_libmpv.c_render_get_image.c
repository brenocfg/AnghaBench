#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpv_render_context {TYPE_2__* renderer; } ;
struct mp_image {int dummy; } ;
struct TYPE_4__ {TYPE_1__* fns; } ;
struct TYPE_3__ {struct mp_image* (* get_image ) (TYPE_2__*,int,int,int,int) ;} ;

/* Variables and functions */
 struct mp_image* stub1 (TYPE_2__*,int,int,int,int) ; 

__attribute__((used)) static struct mp_image *render_get_image(void *ptr, int imgfmt, int w, int h,
                                         int stride_align)
{
    struct mpv_render_context *ctx = ptr;

    return ctx->renderer->fns->get_image(ctx->renderer, imgfmt, w, h, stride_align);
}