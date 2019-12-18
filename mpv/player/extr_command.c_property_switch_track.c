#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct track {int user_tid; char* lang; int /*<<< orphan*/  title; } ;
struct m_property_switch_arg {int /*<<< orphan*/  inc; } ;
struct m_property {int dummy; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;
struct TYPE_11__ {TYPE_1__* opts; int /*<<< orphan*/  playback_initialized; struct track*** current_track; } ;
struct TYPE_10__ {int** stream_id; } ;
typedef  TYPE_2__ MPContext ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_MARK_SELECTION ; 
#define  M_PROPERTY_GET 131 
 int M_PROPERTY_OK ; 
#define  M_PROPERTY_PRINT 130 
#define  M_PROPERTY_SET 129 
#define  M_PROPERTY_SWITCH 128 
 int mp_property_generic_option (TYPE_2__*,struct m_property*,int,void*) ; 
 int /*<<< orphan*/  mp_switch_track_n (TYPE_2__*,int,int,struct track*,int /*<<< orphan*/ ) ; 
 struct track* mp_track_by_tid (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  mp_wakeup_core (TYPE_2__*) ; 
 int /*<<< orphan*/  print_track_list (TYPE_2__*,char*) ; 
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,int,char*,...) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char const*) ; 
 struct track* track_next (TYPE_2__*,int,int,struct track*) ; 

__attribute__((used)) static int property_switch_track(struct m_property *prop, int action, void *arg,
                                 MPContext *mpctx, int order,
                                 enum stream_type type)
{
    struct track *track = mpctx->current_track[order][type];

    switch (action) {
    case M_PROPERTY_GET:
        if (mpctx->playback_initialized) {
            *(int *)arg = track ? track->user_tid : -2;
        } else {
            *(int *)arg = mpctx->opts->stream_id[order][type];
        }
        return M_PROPERTY_OK;
    case M_PROPERTY_PRINT:
        if (track) {
            char *lang = track->lang;
            if (!lang)
                lang = "unknown";

            if (track->title) {
                *(char **)arg = talloc_asprintf(NULL, "(%d) %s (\"%s\")",
                                           track->user_tid, lang, track->title);
            } else {
                *(char **)arg = talloc_asprintf(NULL, "(%d) %s",
                                                track->user_tid, lang);
            }
        } else {
            const char *msg = "no";
            if (!mpctx->playback_initialized &&
                mpctx->opts->stream_id[order][type] == -1)
                msg = "auto";
            *(char **) arg = talloc_strdup(NULL, msg);
        }
        return M_PROPERTY_OK;

    case M_PROPERTY_SWITCH: {
        if (mpctx->playback_initialized) {
            struct m_property_switch_arg *sarg = arg;
            do {
                track = track_next(mpctx, type, sarg->inc >= 0 ? +1 : -1, track);
                mp_switch_track_n(mpctx, order, type, track, FLAG_MARK_SELECTION);
            } while (mpctx->current_track[order][type] != track);
            print_track_list(mpctx, "Track switched:");
        } else {
            // Simply cycle between "no" and "auto". It's possible that this does
            // not always do what the user means, but keep the complexity low.
            mpctx->opts->stream_id[order][type] =
                mpctx->opts->stream_id[order][type] == -1 ? -2 : -1;
        }
        return M_PROPERTY_OK;
    }
    case M_PROPERTY_SET:
        if (mpctx->playback_initialized) {
            track = mp_track_by_tid(mpctx, type, *(int *)arg);
            mp_switch_track_n(mpctx, order, type, track, FLAG_MARK_SELECTION);
            print_track_list(mpctx, "Track switched:");
            mp_wakeup_core(mpctx);
        } else {
            mpctx->opts->stream_id[order][type] = *(int *)arg;
        }
        return M_PROPERTY_OK;
    }
    return mp_property_generic_option(mpctx, prop, action, arg);
}