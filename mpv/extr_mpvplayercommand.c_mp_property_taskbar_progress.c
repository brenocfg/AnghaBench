#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_8__ {scalar_t__ video_out; TYPE_2__* opts; } ;
struct TYPE_7__ {TYPE_1__* vo; } ;
struct TYPE_6__ {int taskbar_progress; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
 int M_PROPERTY_SET ; 
 int mp_property_generic_option (TYPE_3__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  update_vo_playback_state (TYPE_3__*) ; 

__attribute__((used)) static int mp_property_taskbar_progress(void *ctx, struct m_property *prop,
                             int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (action == M_PROPERTY_SET) {
        int desired = !!*(int *) arg;
        if (mpctx->opts->vo->taskbar_progress == desired)
            return M_PROPERTY_OK;
        mpctx->opts->vo->taskbar_progress = desired;
        if (mpctx->video_out)
            update_vo_playback_state(mpctx);
        return M_PROPERTY_OK;
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}