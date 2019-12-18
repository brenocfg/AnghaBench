#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  mouse_event_ts; TYPE_1__* opts; } ;
struct TYPE_6__ {int fullscreen; } ;
struct TYPE_5__ {TYPE_2__* vo; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  VOCTRL_FULLSCREEN ; 
 int mp_property_vo_flag (struct m_property*,int,void*,int /*<<< orphan*/ ,int*,TYPE_3__*) ; 

__attribute__((used)) static int mp_property_fullscreen(void *ctx, struct m_property *prop,
                                  int action, void *arg)
{
    MPContext *mpctx = ctx;
    int oldval = mpctx->opts->vo->fullscreen;
    int r = mp_property_vo_flag(prop, action, arg, VOCTRL_FULLSCREEN,
                                &mpctx->opts->vo->fullscreen, mpctx);
    if (oldval && oldval != mpctx->opts->vo->fullscreen)
        mpctx->mouse_event_ts--; // Show mouse cursor
    return r;
}