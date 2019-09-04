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
struct ra_ctx {int /*<<< orphan*/  vo; struct priv* priv; } ;
struct priv {TYPE_1__* kms; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MP_WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ USE_MASTER ; 
 int /*<<< orphan*/  crtc_release (struct ra_ctx*) ; 
 scalar_t__ drmDropMaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_vt(void *data)
{
    struct ra_ctx *ctx = data;
    MP_VERBOSE(ctx->vo, "Releasing VT\n");
    crtc_release(ctx);
    if (USE_MASTER) {
        //this function enables support for switching to x, weston etc.
        //however, for whatever reason, it can be called only by root users.
        //until things change, this is commented.
        struct priv *p = ctx->priv;
        if (drmDropMaster(p->kms->fd)) {
            MP_WARN(ctx->vo, "Failed to drop DRM master: %s\n",
                    mp_strerror(errno));
        }
    }
}