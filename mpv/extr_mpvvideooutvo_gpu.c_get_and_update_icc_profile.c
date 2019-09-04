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
struct gpu_priv {int /*<<< orphan*/  renderer; int /*<<< orphan*/  events; TYPE_2__* ctx; } ;
typedef  int /*<<< orphan*/  bstr ;
struct TYPE_4__ {TYPE_1__* fns; } ;
struct TYPE_3__ {int (* control ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct gpu_priv*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct gpu_priv*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct gpu_priv*,char*) ; 
 int /*<<< orphan*/  VOCTRL_GET_ICC_PROFILE ; 
 int VO_FALSE ; 
 int VO_NOTAVAIL ; 
 int VO_NOTIMPL ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ *) ; 
 scalar_t__ gl_video_icc_auto_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_video_set_icc_profile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_and_update_icc_profile(struct gpu_priv *p)
{
    if (gl_video_icc_auto_enabled(p->renderer)) {
        MP_VERBOSE(p, "Querying ICC profile...\n");
        bstr icc = bstr0(NULL);
        int r = p->ctx->fns->control(p->ctx, &p->events, VOCTRL_GET_ICC_PROFILE, &icc);

        if (r != VO_NOTAVAIL) {
            if (r == VO_FALSE) {
                MP_WARN(p, "Could not retrieve an ICC profile.\n");
            } else if (r == VO_NOTIMPL) {
                MP_ERR(p, "icc-profile-auto not implemented on this platform.\n");
            }

            gl_video_set_icc_profile(p->renderer, icc);
        }
    }
}