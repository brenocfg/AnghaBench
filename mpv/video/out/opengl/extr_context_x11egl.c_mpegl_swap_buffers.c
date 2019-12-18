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
struct priv {int /*<<< orphan*/  sync; int /*<<< orphan*/  egl_surface; int /*<<< orphan*/  egl_display; int /*<<< orphan*/  (* GetSyncValues ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ;} ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oml_sync_swap (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 

__attribute__((used)) static void mpegl_swap_buffers(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    eglSwapBuffers(p->egl_display, p->egl_surface);

    int64_t ust, msc, sbc;
    if (!p->GetSyncValues || !p->GetSyncValues(p->egl_display, p->egl_surface,
                                               &ust, &msc, &sbc))
        ust = msc = sbc = -1;

    oml_sync_swap(&p->sync, ust, msc, sbc);
}