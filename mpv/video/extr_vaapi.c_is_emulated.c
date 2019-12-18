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
struct AVBufferRef {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__* hwctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ AVVAAPIDeviceContext ;
typedef  TYPE_2__ AVHWDeviceContext ;

/* Variables and functions */
 scalar_t__ strstr (char const*,char*) ; 
 char* vaQueryVendorString (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_emulated(struct AVBufferRef *hw_device_ctx)
{
    AVHWDeviceContext *hwctx = (void *)hw_device_ctx->data;
    AVVAAPIDeviceContext *vactx = hwctx->hwctx;

    const char *s = vaQueryVendorString(vactx->display);
    return s && strstr(s, "VDPAU backend");
}