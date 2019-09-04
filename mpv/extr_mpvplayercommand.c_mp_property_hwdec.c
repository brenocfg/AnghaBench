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
struct track {struct mp_decoder_wrapper* dec; } ;
struct mp_decoder_wrapper {int dummy; } ;
struct m_property {int dummy; } ;
struct TYPE_4__ {double last_vo_pts; struct track*** current_track; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  MPSEEK_ABSOLUTE ; 
 int /*<<< orphan*/  MPSEEK_EXACT ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  M_PROPERTY_GET ; 
 int M_PROPERTY_OK ; 
 int M_PROPERTY_SET ; 
 size_t STREAM_VIDEO ; 
 int /*<<< orphan*/  VDCTRL_REINIT ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int bstr_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_decoder_wrapper_control (struct mp_decoder_wrapper*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mp_property_generic_option (TYPE_1__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  queue_seek (TYPE_1__*,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static int mp_property_hwdec(void *ctx, struct m_property *prop,
                             int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct track *track = mpctx->current_track[0][STREAM_VIDEO];
    struct mp_decoder_wrapper *dec = track ? track->dec : NULL;

    if (action == M_PROPERTY_SET) {
        char *new = *(char **)arg;
        char *old = NULL;
        if (mp_property_generic_option(mpctx, prop, M_PROPERTY_GET, &old) < 1)
            old = NULL;

        bool same = bstr_equals(bstr0(old), bstr0(new));

        mp_property_generic_option(mpctx, prop, M_PROPERTY_SET, &new);

        talloc_free(old);

        if (!dec || same)
            return M_PROPERTY_OK;

        mp_decoder_wrapper_control(dec, VDCTRL_REINIT, NULL);
        double last_pts = mpctx->last_vo_pts;
        if (last_pts != MP_NOPTS_VALUE)
            queue_seek(mpctx, MPSEEK_ABSOLUTE, last_pts, MPSEEK_EXACT, 0);

        return M_PROPERTY_OK;
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}