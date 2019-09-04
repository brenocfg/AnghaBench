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
struct vo {int dummy; } ;
struct MPContext {int /*<<< orphan*/  mconfig; TYPE_2__* opts; struct vo* video_out; } ;
struct TYPE_4__ {TYPE_1__* vo; } ;
struct TYPE_3__ {int fullscreen; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_EVENT_WIN_RESIZE ; 
 int /*<<< orphan*/  MP_EVENT_WIN_STATE ; 
 int /*<<< orphan*/  VOCTRL_GET_FULLSCREEN ; 
 int /*<<< orphan*/  VO_EVENTS_USER ; 
 int VO_EVENT_FULLSCREEN_STATE ; 
 int VO_EVENT_RESIZE ; 
 int VO_EVENT_WIN_STATE ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  m_config_get_co (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_config_set_option_raw_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vo_control (struct vo*,int /*<<< orphan*/ ,int*) ; 
 int vo_query_and_reset_events (struct vo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_vo_events(struct MPContext *mpctx)
{
    struct vo *vo = mpctx->video_out;
    int events = vo ? vo_query_and_reset_events(vo, VO_EVENTS_USER) : 0;
    if (events & VO_EVENT_RESIZE)
        mp_notify(mpctx, MP_EVENT_WIN_RESIZE, NULL);
    if (events & VO_EVENT_WIN_STATE)
        mp_notify(mpctx, MP_EVENT_WIN_STATE, NULL);
    if (events & VO_EVENT_FULLSCREEN_STATE) {
        // The only purpose of this is to update the fullscreen flag on the
        // playloop side if it changes "from outside" on the VO.
        int fs = mpctx->opts->vo->fullscreen;
        vo_control(vo, VOCTRL_GET_FULLSCREEN, &fs);
        m_config_set_option_raw_direct(mpctx->mconfig,
            m_config_get_co(mpctx->mconfig, bstr0("fullscreen")), &fs, 0);
    }
}