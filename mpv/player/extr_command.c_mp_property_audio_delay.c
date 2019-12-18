#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m_property {int dummy; } ;
struct TYPE_6__ {float delay; TYPE_1__* opts; int /*<<< orphan*/  vo_chain; int /*<<< orphan*/  ao_chain; } ;
struct TYPE_5__ {float audio_delay; } ;
typedef  TYPE_2__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 129 
#define  M_PROPERTY_SET 128 
 char* format_delay (float) ; 
 int mp_property_generic_option (TYPE_2__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_2__*) ; 

__attribute__((used)) static int mp_property_audio_delay(void *ctx, struct m_property *prop,
                                   int action, void *arg)
{
    MPContext *mpctx = ctx;
    float delay = mpctx->opts->audio_delay;
    switch (action) {
    case M_PROPERTY_PRINT:
        *(char **)arg = format_delay(delay);
        return M_PROPERTY_OK;
    case M_PROPERTY_SET: {
        int r = mp_property_generic_option(mpctx, prop, action, arg);
        if (mpctx->ao_chain && mpctx->vo_chain)
            mpctx->delay += mpctx->opts->audio_delay - delay;
        mp_wakeup_core(mpctx);
        return r;
    }
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}