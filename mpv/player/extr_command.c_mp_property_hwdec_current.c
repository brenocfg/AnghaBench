#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct track {struct mp_decoder_wrapper* dec; } ;
struct mp_decoder_wrapper {int dummy; } ;
struct m_property {int dummy; } ;
struct TYPE_2__ {struct track*** current_track; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 size_t STREAM_VIDEO ; 
 int /*<<< orphan*/  VDCTRL_GET_HWDEC ; 
 int m_property_strdup_ro (int,void*,char*) ; 
 int /*<<< orphan*/  mp_decoder_wrapper_control (struct mp_decoder_wrapper*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int mp_property_hwdec_current(void *ctx, struct m_property *prop,
                                     int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct track *track = mpctx->current_track[0][STREAM_VIDEO];
    struct mp_decoder_wrapper *dec = track ? track->dec : NULL;

    if (!dec)
        return M_PROPERTY_UNAVAILABLE;

    char *current = NULL;
    mp_decoder_wrapper_control(dec, VDCTRL_GET_HWDEC, &current);
    if (!current)
        current = "no";
    return m_property_strdup_ro(action, arg, current);
}