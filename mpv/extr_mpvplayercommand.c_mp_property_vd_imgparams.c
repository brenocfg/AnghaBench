#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vo_chain {TYPE_2__* filter; } ;
struct track {TYPE_1__* stream; } ;
struct mp_codec_params {scalar_t__ disp_h; scalar_t__ disp_w; } ;
struct m_sub_property {char* member_0; int /*<<< orphan*/  member_1; } ;
struct m_property {int dummy; } ;
struct TYPE_8__ {scalar_t__ imgfmt; } ;
struct TYPE_7__ {struct track*** current_track; struct vo_chain* vo_chain; } ;
struct TYPE_6__ {TYPE_4__ input_params; } ;
struct TYPE_5__ {struct mp_codec_params* codec; } ;
typedef  TYPE_3__ MPContext ;

/* Variables and functions */
 int M_PROPERTY_UNAVAILABLE ; 
 size_t STREAM_VIDEO ; 
 int /*<<< orphan*/  SUB_PROP_INT (scalar_t__) ; 
 int m_property_read_sub (struct m_sub_property*,int,void*) ; 
 int property_imgparams (TYPE_4__,int,void*) ; 

__attribute__((used)) static int mp_property_vd_imgparams(void *ctx, struct m_property *prop,
                                    int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct vo_chain *vo_c = mpctx->vo_chain;
    if (!vo_c)
        return M_PROPERTY_UNAVAILABLE;
    struct track *track = mpctx->current_track[0][STREAM_VIDEO];
    struct mp_codec_params *c =
        track && track->stream ? track->stream->codec : NULL;
    if (vo_c->filter->input_params.imgfmt) {
        return property_imgparams(vo_c->filter->input_params, action, arg);
    } else if (c && c->disp_w && c->disp_h) {
        // Simplistic fallback for stupid scripts querying "width"/"height"
        // before the first frame is decoded.
        struct m_sub_property props[] = {
            {"w", SUB_PROP_INT(c->disp_w)},
            {"h", SUB_PROP_INT(c->disp_h)},
            {0}
        };
        return m_property_read_sub(props, action, arg);
    }
    return M_PROPERTY_UNAVAILABLE;
}