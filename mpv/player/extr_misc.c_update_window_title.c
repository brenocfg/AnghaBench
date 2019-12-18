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
struct MPContext {char* last_window_title; scalar_t__ ao; scalar_t__ video_out; TYPE_1__* opts; } ;
struct TYPE_2__ {int /*<<< orphan*/  wintitle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOCONTROL_UPDATE_STREAM_TITLE ; 
 int /*<<< orphan*/  VOCTRL_UPDATE_WINDOW_TITLE ; 
 int /*<<< orphan*/  ao_control (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 char* mp_property_expand_string (struct MPContext*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_steal (struct MPContext*,char*) ; 
 int /*<<< orphan*/  vo_control (scalar_t__,int /*<<< orphan*/ ,char*) ; 

void update_window_title(struct MPContext *mpctx, bool force)
{
    if (!mpctx->video_out && !mpctx->ao) {
        talloc_free(mpctx->last_window_title);
        mpctx->last_window_title = NULL;
        return;
    }
    char *title = mp_property_expand_string(mpctx, mpctx->opts->wintitle);
    if (!mpctx->last_window_title || force ||
        strcmp(title, mpctx->last_window_title) != 0)
    {
        talloc_free(mpctx->last_window_title);
        mpctx->last_window_title = talloc_steal(mpctx, title);

        if (mpctx->video_out)
            vo_control(mpctx->video_out, VOCTRL_UPDATE_WINDOW_TITLE, title);

        if (mpctx->ao) {
            ao_control(mpctx->ao, AOCONTROL_UPDATE_STREAM_TITLE, title);
        }
    } else {
        talloc_free(title);
    }
}