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
struct mp_vaapi_ctx {int /*<<< orphan*/ * av_device_ref; } ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ **) ; 

void va_destroy(struct mp_vaapi_ctx *ctx)
{
    if (!ctx)
        return;

    AVBufferRef *ref = ctx->av_device_ref;
    av_buffer_unref(&ref); // frees ctx as well
}