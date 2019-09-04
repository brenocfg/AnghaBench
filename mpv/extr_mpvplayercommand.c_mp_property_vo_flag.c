#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_4__ {scalar_t__ video_out; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_SET ; 
 int mp_property_generic_option (TYPE_1__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  vo_control (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_vo_flag(struct m_property *prop, int action, void *arg,
                               int vo_ctrl, int *vo_var, MPContext *mpctx)
{
    int old = *vo_var;
    int res = mp_property_generic_option(mpctx, prop, action, arg);
    if (action == M_PROPERTY_SET && old != *vo_var) {
        if (mpctx->video_out)
            vo_control(mpctx->video_out, vo_ctrl, 0);
    }
    return res;
}