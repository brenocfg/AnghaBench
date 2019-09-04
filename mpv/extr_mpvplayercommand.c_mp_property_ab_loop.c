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
struct m_property {int /*<<< orphan*/  name; } ;
struct MPOpts {scalar_t__* ab_loop; } ;
struct MPContext {int ab_loop_clip; scalar_t__ playback_pts; struct MPOpts* opts; } ;

/* Variables and functions */
 scalar_t__ MP_NOPTS_VALUE ; 
 int M_PROPERTY_ERROR ; 
 int /*<<< orphan*/  M_PROPERTY_GET ; 
 int M_PROPERTY_KEY_ACTION ; 
 int M_PROPERTY_SET ; 
 int /*<<< orphan*/  OSD_BAR_SEEK ; 
 int mp_property_generic_option (struct MPContext*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int property_time (int,void*,double) ; 
 int /*<<< orphan*/  set_osd_bar_chapters (struct MPContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mp_property_ab_loop(void *ctx, struct m_property *prop,
                               int action, void *arg)
{
    struct MPContext *mpctx = ctx;
    struct MPOpts *opts = mpctx->opts;
    if (action == M_PROPERTY_KEY_ACTION) {
        double val;
        if (mp_property_generic_option(mpctx, prop, M_PROPERTY_GET, &val) < 1)
            return M_PROPERTY_ERROR;

        return property_time(action, arg, val);
    }
    int r = mp_property_generic_option(mpctx, prop, action, arg);
    if (r > 0 && action == M_PROPERTY_SET) {
        mpctx->ab_loop_clip = mpctx->playback_pts < opts->ab_loop[1];
        if (strcmp(prop->name, "ab-loop-b") == 0) {
            if (opts->ab_loop[1] != MP_NOPTS_VALUE &&
                mpctx->playback_pts <= opts->ab_loop[1])
                mpctx->ab_loop_clip = true;
        }
        // Update if visible
        set_osd_bar_chapters(mpctx, OSD_BAR_SEEK);
        mp_wakeup_core(mpctx);
    }
    return r;
}