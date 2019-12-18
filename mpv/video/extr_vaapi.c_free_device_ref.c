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
struct mp_vaapi_ctx {int /*<<< orphan*/  native_ctx; int /*<<< orphan*/  (* destroy_native_ctx ) (int /*<<< orphan*/ ) ;scalar_t__ display; } ;
struct AVHWDeviceContext {struct mp_vaapi_ctx* user_opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct mp_vaapi_ctx*) ; 
 int /*<<< orphan*/  vaTerminate (scalar_t__) ; 

__attribute__((used)) static void free_device_ref(struct AVHWDeviceContext *hwctx)
{
    struct mp_vaapi_ctx *ctx = hwctx->user_opaque;

    if (ctx->display)
        vaTerminate(ctx->display);

    if (ctx->destroy_native_ctx)
        ctx->destroy_native_ctx(ctx->native_ctx);

    talloc_free(ctx);
}