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
struct TYPE_2__ {scalar_t__ hwdec_devs; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_filter {int /*<<< orphan*/  log; int /*<<< orphan*/  global; TYPE_1__* priv; } ;
struct hwdec_info {int /*<<< orphan*/  lavc_device; scalar_t__ copying; } ;
struct hwcontext_fns {int /*<<< orphan*/ * (* create_dev ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hwcontext_create_dev_params*) ;} ;
struct hwcontext_create_dev_params {int probing; } ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_hwdevice_ctx_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hwdec_devices_get_lavc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwdec_devices_request_all (scalar_t__) ; 
 struct hwcontext_fns* hwdec_get_hwcontext_fns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hwcontext_create_dev_params*) ; 

__attribute__((used)) static AVBufferRef *hwdec_create_dev(struct mp_filter *vd,
                                     struct hwdec_info *hwdec,
                                     bool autoprobe)
{
    vd_ffmpeg_ctx *ctx = vd->priv;
    assert(hwdec->lavc_device);

    if (hwdec->copying) {
        const struct hwcontext_fns *fns =
            hwdec_get_hwcontext_fns(hwdec->lavc_device);
        if (fns && fns->create_dev) {
            struct hwcontext_create_dev_params params = {
                .probing = autoprobe,
            };
            return fns->create_dev(vd->global, vd->log, &params);
        } else {
            AVBufferRef* ref = NULL;
            av_hwdevice_ctx_create(&ref, hwdec->lavc_device, NULL, NULL, 0);
            return ref;
        }
    } else if (ctx->hwdec_devs) {
        hwdec_devices_request_all(ctx->hwdec_devs);
        return hwdec_devices_get_lavc(ctx->hwdec_devs, hwdec->lavc_device);
    }

    return NULL;
}