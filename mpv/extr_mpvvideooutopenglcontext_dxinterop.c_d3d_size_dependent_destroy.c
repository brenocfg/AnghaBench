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
struct ra_ctx {struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* DeleteTextures ) (int,scalar_t__*) ;int /*<<< orphan*/  (* DXUnregisterObjectNV ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* DXUnlockObjectsNV ) (int /*<<< orphan*/ ,int,scalar_t__*) ;} ;
struct priv {int /*<<< orphan*/  swapchain; int /*<<< orphan*/  backbuffer; int /*<<< orphan*/  rtarget; scalar_t__ texture; scalar_t__ rtarget_h; int /*<<< orphan*/  device_h; TYPE_1__ gl; } ;
typedef  TYPE_1__ GL ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int,scalar_t__*) ; 

__attribute__((used)) static void d3d_size_dependent_destroy(struct ra_ctx *ctx)
{
    struct priv *p = ctx->priv;
    GL *gl = &p->gl;

    if (p->rtarget_h) {
        gl->DXUnlockObjectsNV(p->device_h, 1, &p->rtarget_h);
        gl->DXUnregisterObjectNV(p->device_h, p->rtarget_h);
    }
    p->rtarget_h = 0;
    if (p->texture)
        gl->DeleteTextures(1, &p->texture);
    p->texture = 0;

    SAFE_RELEASE(p->rtarget);
    SAFE_RELEASE(p->backbuffer);
    SAFE_RELEASE(p->swapchain);
}