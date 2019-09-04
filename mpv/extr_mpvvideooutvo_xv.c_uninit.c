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
struct xvctx {int num_buffers; scalar_t__ f_gc; scalar_t__ vo_gc; int /*<<< orphan*/ * fo; int /*<<< orphan*/ * ai; int /*<<< orphan*/  original_image; } ;
struct vo {TYPE_1__* x11; struct xvctx* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 scalar_t__ None ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XvFreeAdaptorInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deallocate_xvimage (struct vo*,int) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_x11_uninit (struct vo*) ; 

__attribute__((used)) static void uninit(struct vo *vo)
{
    struct xvctx *ctx = vo->priv;
    int i;

    talloc_free(ctx->original_image);

    if (ctx->ai)
        XvFreeAdaptorInfo(ctx->ai);
    ctx->ai = NULL;
    if (ctx->fo) {
        XFree(ctx->fo);
        ctx->fo = NULL;
    }
    for (i = 0; i < ctx->num_buffers; i++)
        deallocate_xvimage(vo, i);
    if (ctx->f_gc != None)
        XFreeGC(vo->x11->display, ctx->f_gc);
    if (ctx->vo_gc != None)
        XFreeGC(vo->x11->display, ctx->vo_gc);
    // uninit() shouldn't get called unless initialization went past vo_init()
    vo_x11_uninit(vo);
}