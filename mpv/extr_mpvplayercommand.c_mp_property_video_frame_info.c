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
struct mp_image {int pict_type; int fields; } ;
struct m_sub_property {char* member_0; int unavailable; int /*<<< orphan*/  member_1; } ;
struct m_property {int dummy; } ;
struct TYPE_2__ {scalar_t__ video_out; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */
 int MP_IMGFIELD_INTERLACED ; 
 int MP_IMGFIELD_REPEAT_FIRST ; 
 int MP_IMGFIELD_TOP_FIRST ; 
 int M_PROPERTY_UNAVAILABLE ; 
 int /*<<< orphan*/  SUB_PROP_FLAG (int) ; 
 int /*<<< orphan*/  SUB_PROP_STR (char const*) ; 
 int m_property_read_sub (struct m_sub_property*,int,void*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 struct mp_image* vo_get_current_frame (scalar_t__) ; 

__attribute__((used)) static int mp_property_video_frame_info(void *ctx, struct m_property *prop,
                                        int action, void *arg)
{
    MPContext *mpctx = ctx;
    struct mp_image *f =
        mpctx->video_out ? vo_get_current_frame(mpctx->video_out) : NULL;
    if (!f)
        return M_PROPERTY_UNAVAILABLE;

    const char *pict_types[] = {0, "I", "P", "B"};
    const char *pict_type = f->pict_type >= 1 && f->pict_type <= 3
                          ? pict_types[f->pict_type] : NULL;

    struct m_sub_property props[] = {
        {"picture-type",    SUB_PROP_STR(pict_type), .unavailable = !pict_type},
        {"interlaced",      SUB_PROP_FLAG(!!(f->fields & MP_IMGFIELD_INTERLACED))},
        {"tff",             SUB_PROP_FLAG(!!(f->fields & MP_IMGFIELD_TOP_FIRST))},
        {"repeat",          SUB_PROP_FLAG(!!(f->fields & MP_IMGFIELD_REPEAT_FIRST))},
        {0}
    };

    talloc_free(f);
    return m_property_read_sub(props, action, arg);
}