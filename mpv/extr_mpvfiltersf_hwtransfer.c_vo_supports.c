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
struct mp_hwdec_ctx {int hw_imgfmt; int* supported_formats; } ;

/* Variables and functions */

__attribute__((used)) static bool vo_supports(struct mp_hwdec_ctx *ctx, int hw_fmt, int sw_fmt)
{
    if (!ctx->hw_imgfmt)
        return true; // if unset, all formats are allowed
    if (ctx->hw_imgfmt != hw_fmt)
        return false;

    for (int i = 0; ctx->supported_formats &&  ctx->supported_formats[i]; i++) {
        if (ctx->supported_formats[i] == sw_fmt)
            return true;
    }

    return false;
}