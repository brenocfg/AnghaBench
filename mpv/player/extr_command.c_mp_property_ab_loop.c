#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct m_property {int dummy; } ;
struct MPContext {int dummy; } ;

/* Variables and functions */
 int M_PROPERTY_ERROR ; 
 int /*<<< orphan*/  M_PROPERTY_GET ; 
 int M_PROPERTY_KEY_ACTION ; 
 int M_PROPERTY_SET ; 
 int /*<<< orphan*/  OSD_BAR_SEEK ; 
 int mp_property_generic_option (struct MPContext*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int property_time (int,void*,double) ; 
 int /*<<< orphan*/  set_osd_bar_chapters (struct MPContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_ab_loop_clip (struct MPContext*) ; 

__attribute__((used)) static int mp_property_ab_loop(void *ctx, struct m_property *prop,
                               int action, void *arg)
{
    struct MPContext *mpctx = ctx;
    if (action == M_PROPERTY_KEY_ACTION) {
        double val;
        if (mp_property_generic_option(mpctx, prop, M_PROPERTY_GET, &val) < 1)
            return M_PROPERTY_ERROR;

        return property_time(action, arg, val);
    }
    int r = mp_property_generic_option(mpctx, prop, action, arg);
    if (r > 0 && action == M_PROPERTY_SET) {
        update_ab_loop_clip(mpctx);
        // Update if visible
        set_osd_bar_chapters(mpctx, OSD_BAR_SEEK);
        mp_wakeup_core(mpctx);
    }
    return r;
}