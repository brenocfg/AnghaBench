#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo_chain {TYPE_1__* track; } ;
struct mp_image_params {int /*<<< orphan*/  imgfmt; int /*<<< orphan*/  member_0; } ;
struct m_property {int dummy; } ;
struct TYPE_4__ {struct vo_chain* vo_chain; } ;
struct TYPE_3__ {int /*<<< orphan*/  dec; } ;
typedef  TYPE_2__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  mp_decoder_wrapper_get_video_dec_params (int /*<<< orphan*/ ,struct mp_image_params*) ; 
 int property_imgparams (struct mp_image_params,int,void*) ; 

__attribute__((used)) static int mp_property_dec_imgparams(void *ctx, struct m_property *prop,
                                    int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct mp_image_params p = {0};
    struct vo_chain *vo_c = mpctx->vo_chain;
    if (vo_c && vo_c->track)
        mp_decoder_wrapper_get_video_dec_params(vo_c->track->dec, &p);
    if (!p.imgfmt)
        return M_PROPERTY_UNAVAILABLE;
    return property_imgparams(p, action, arg);
}