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
struct xvctx {size_t current_buf; int num_buffers; int /*<<< orphan*/  Shmem_Flag; int /*<<< orphan*/ * xvimage; } ;
struct vo {TYPE_1__* x11; struct xvctx* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_xvimage (struct vo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flip_page(struct vo *vo)
{
    struct xvctx *ctx = vo->priv;
    put_xvimage(vo, ctx->xvimage[ctx->current_buf]);

    /* remember the currently visible buffer */
    ctx->current_buf = (ctx->current_buf + 1) % ctx->num_buffers;

    if (!ctx->Shmem_Flag)
        XSync(vo->x11->display, False);
}