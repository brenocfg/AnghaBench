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
struct ra_ctx {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  hdc; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_context_wgl_gl3 (struct ra_ctx*) ; 
 int /*<<< orphan*/  create_context_wgl_old (struct ra_ctx*) ; 
 int /*<<< orphan*/  create_dc (struct ra_ctx*) ; 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_ctx(void *ptr)
{
    struct ra_ctx *ctx = ptr;
    struct priv *p = ctx->priv;

    if (!create_dc(ctx))
        return;

    create_context_wgl_gl3(ctx);
    if (!p->context)
        create_context_wgl_old(ctx);

    wglMakeCurrent(p->hdc, NULL);
}