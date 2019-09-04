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
struct MPContext {TYPE_1__* opts; int /*<<< orphan*/  log; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;
struct TYPE_2__ {int /*<<< orphan*/  osd_duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ON_OSD_MSG ; 
 int edit_filters (struct MPContext*,int /*<<< orphan*/ ,int,char const*,char const*) ; 
 char** filter_opt ; 
 int /*<<< orphan*/  set_osd_msg (struct MPContext*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_property_osd (struct MPContext*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edit_filters_osd(struct MPContext *mpctx, enum stream_type mediatype,
                            const char *cmd, const char *arg, bool on_osd)
{
    int r = edit_filters(mpctx, mpctx->log, mediatype, cmd, arg);
    if (on_osd) {
        if (r >= 0) {
            const char *prop = filter_opt[mediatype];
            show_property_osd(mpctx, prop, MP_ON_OSD_MSG);
        } else {
            set_osd_msg(mpctx, 1, mpctx->opts->osd_duration,
                         "Changing filters failed!");
        }
    }
    return r;
}