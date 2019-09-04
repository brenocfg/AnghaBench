#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_6__ {TYPE_2__* vo_chain; } ;
struct TYPE_5__ {TYPE_1__* filter; } ;
struct TYPE_4__ {float container_fps; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  isfinite (float) ; 
 int m_property_float_ro (int,void*,float) ; 

__attribute__((used)) static int mp_property_fps(void *ctx, struct m_property *prop,
                           int action, void *arg)
{
    MPContext *mpctx = ctx;
    float fps = mpctx->vo_chain ? mpctx->vo_chain->filter->container_fps : 0;
    if (fps < 0.1 || !isfinite(fps))
        return M_PROPERTY_UNAVAILABLE;;
    return m_property_float_ro(action, arg, fps);
}