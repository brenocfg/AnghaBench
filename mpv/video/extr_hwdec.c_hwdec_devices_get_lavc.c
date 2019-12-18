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
struct mp_hwdec_devices {int dummy; } ;
struct mp_hwdec_ctx {int /*<<< orphan*/  av_device_ref; } ;
struct AVBufferRef {int dummy; } ;

/* Variables and functions */
 struct AVBufferRef* av_buffer_ref (int /*<<< orphan*/ ) ; 
 struct mp_hwdec_ctx* hwdec_devices_get_by_lavc (struct mp_hwdec_devices*,int) ; 

struct AVBufferRef *hwdec_devices_get_lavc(struct mp_hwdec_devices *devs,
                                           int av_hwdevice_type)
{
    struct mp_hwdec_ctx *ctx = hwdec_devices_get_by_lavc(devs, av_hwdevice_type);
    if (!ctx)
        return NULL;
    return av_buffer_ref(ctx->av_device_ref);
}