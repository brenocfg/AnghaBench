#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vo_chain; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 double calc_average_frame_duration (TYPE_1__*) ; 
 int m_property_double_ro (int,void*,double) ; 

__attribute__((used)) static int mp_property_vf_fps(void *ctx, struct m_property *prop,
                              int action, void *arg)
{
    MPContext *mpctx = ctx;
    if (!mpctx->vo_chain)
        return M_PROPERTY_UNAVAILABLE;
    double avg = calc_average_frame_duration(mpctx);
    if (avg <= 0)
        return M_PROPERTY_UNAVAILABLE;
    return m_property_double_ro(action, arg, 1.0 / avg);
}