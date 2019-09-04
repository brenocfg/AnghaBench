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
struct mp_decoder_wrapper {int /*<<< orphan*/  dropped_frames; } ;
struct m_property {int dummy; } ;
struct TYPE_6__ {TYPE_2__* vo_chain; } ;
struct TYPE_5__ {TYPE_1__* track; } ;
struct TYPE_4__ {struct mp_decoder_wrapper* dec; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 int m_property_int_ro (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mp_property_frame_drop_dec(void *ctx, struct m_property *prop,
                                      int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct mp_decoder_wrapper *dec = mpctx->vo_chain && mpctx->vo_chain->track
        ? mpctx->vo_chain->track->dec : NULL;
    if (!dec)
        return M_PROPERTY_UNAVAILABLE;

    return m_property_int_ro(action, arg, dec->dropped_frames);
}