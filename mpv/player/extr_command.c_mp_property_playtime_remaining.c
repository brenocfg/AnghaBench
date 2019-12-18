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
struct TYPE_3__ {double video_speed; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 int property_time (int,void*,double) ; 
 int /*<<< orphan*/  time_remaining (TYPE_1__*,double*) ; 

__attribute__((used)) static int mp_property_playtime_remaining(void *ctx, struct m_property *prop,
                                          int action, void *arg)
{
    MPContext *mpctx = ctx;
    double remaining;
    if (!time_remaining(mpctx, &remaining))
        return M_PROPERTY_UNAVAILABLE;

    double speed = mpctx->video_speed;
    return property_time(action, arg, remaining / speed);
}