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
struct m_option {scalar_t__ max; } ;
struct demuxer {scalar_t__ num_editions; int edition; } ;
struct TYPE_4__ {int /*<<< orphan*/  stop_play; int /*<<< orphan*/  playback_initialized; struct demuxer* demuxer; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
#define  M_PROPERTY_GET 130 
#define  M_PROPERTY_GET_CONSTRICTED_TYPE 129 
 int M_PROPERTY_GET_TYPE ; 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_SET 128 
 int /*<<< orphan*/  PT_CURRENT_ENTRY ; 
 int mp_property_generic_option (TYPE_1__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_1__*) ; 

__attribute__((used)) static int mp_property_edition(void *ctx, struct m_property *prop,
                               int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct demuxer *demuxer = mpctx->demuxer;
    if (!mpctx->playback_initialized || !demuxer || demuxer->num_editions <= 0)
        return mp_property_generic_option(mpctx, prop, action, arg);

    int edition = demuxer->edition;

    switch (action) {
    case M_PROPERTY_GET:
        *(int *)arg = edition;
        return M_PROPERTY_OK;
    case M_PROPERTY_SET: {
        edition = *(int *)arg;
        if (edition != demuxer->edition) {
            if (!mpctx->stop_play)
                mpctx->stop_play = PT_CURRENT_ENTRY;
            mp_wakeup_core(mpctx);
            break; // write value, trigger option change notify
        }
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_GET_CONSTRICTED_TYPE: {
        int r = mp_property_generic_option(mpctx, prop, M_PROPERTY_GET_TYPE, arg);
        ((struct m_option *)arg)->max = demuxer->num_editions - 1;
        return r;
    }
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}