#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_7__ {TYPE_1__* opts; } ;
struct TYPE_6__ {double playback_speed; } ;
typedef  TYPE_2__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 129 
#define  M_PROPERTY_SET 128 
 int mp_property_generic_option (TYPE_2__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_2__*) ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  update_playback_speed (TYPE_2__*) ; 

__attribute__((used)) static int mp_property_playback_speed(void *ctx, struct m_property *prop,
                                      int action, void *arg)
{
    MPContext *mpctx = ctx;
    double speed = mpctx->opts->playback_speed;
    switch (action) {
    case M_PROPERTY_SET: {
        int r = mp_property_generic_option(mpctx, prop, action, arg);
        update_playback_speed(mpctx);
        mp_wakeup_core(mpctx);
        return r;
    }
    case M_PROPERTY_PRINT:
        *(char **)arg = talloc_asprintf(NULL, "%.2f", speed);
        return M_PROPERTY_OK;
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}