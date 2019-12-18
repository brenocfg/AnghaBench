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
struct track {int is_external; int no_default; int no_auto_select; void* external_filename; void* title; } ;
struct sh_stream {int type; char* title; } ;
struct mp_cancel {int dummy; } ;
struct demuxer_params {int is_top_level; int /*<<< orphan*/  force_format; } ;
struct demuxer {int /*<<< orphan*/  cancel; int /*<<< orphan*/  start_time; } ;
struct MPOpts {scalar_t__ rebase_start_time; int /*<<< orphan*/  audio_demuxer_name; int /*<<< orphan*/  sub_demuxer_name; } ;
struct MPContext {int num_tracks; int /*<<< orphan*/  playback_abort; scalar_t__ stop_play; int /*<<< orphan*/  global; struct MPOpts* opts; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*,char*,...) ; 
#define  STREAM_AUDIO 129 
#define  STREAM_SUB 128 
 int STREAM_TYPE_COUNT ; 
 struct track* add_stream_track (struct MPContext*,struct demuxer*,struct sh_stream*) ; 
 int /*<<< orphan*/  demux_cancel_and_free (struct demuxer*) ; 
 int demux_get_num_stream (struct demuxer*) ; 
 struct sh_stream* demux_get_stream (struct demuxer*,int) ; 
 struct demuxer* demux_open_url (char*,struct demuxer_params*,struct mp_cancel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_set_ts_offset (struct demuxer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_demux_thread (struct MPContext*,struct demuxer*) ; 
 char* mp_basename (char*) ; 
 int /*<<< orphan*/  mp_cancel_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_cancel_test (struct mp_cancel*) ; 
 int /*<<< orphan*/  mp_core_lock (struct MPContext*) ; 
 int /*<<< orphan*/  mp_core_unlock (struct MPContext*) ; 
 char* mp_tprintf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_type_name (int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 void* talloc_strdup (struct track*,char*) ; 

int mp_add_external_file(struct MPContext *mpctx, char *filename,
                         enum stream_type filter, struct mp_cancel *cancel)
{
    struct MPOpts *opts = mpctx->opts;
    if (!filename || mp_cancel_test(cancel))
        return -1;

    char *disp_filename = filename;
    if (strncmp(disp_filename, "memory://", 9) == 0)
        disp_filename = "memory://"; // avoid noise

    struct demuxer_params params = {
        .is_top_level = true,
    };

    switch (filter) {
    case STREAM_SUB:
        params.force_format = opts->sub_demuxer_name;
        break;
    case STREAM_AUDIO:
        params.force_format = opts->audio_demuxer_name;
        break;
    }

    mp_core_unlock(mpctx);

    struct demuxer *demuxer =
        demux_open_url(filename, &params, cancel, mpctx->global);
    if (demuxer)
        enable_demux_thread(mpctx, demuxer);

    mp_core_lock(mpctx);

    // The command could have overlapped with playback exiting. (We don't care
    // if playback has started again meanwhile - weird, but not a problem.)
    if (mpctx->stop_play)
        goto err_out;

    if (!demuxer)
        goto err_out;

    if (filter != STREAM_SUB && opts->rebase_start_time)
        demux_set_ts_offset(demuxer, -demuxer->start_time);

    bool has_any = false;
    for (int n = 0; n < demux_get_num_stream(demuxer); n++) {
        struct sh_stream *sh = demux_get_stream(demuxer, n);
        if (sh->type == filter || filter == STREAM_TYPE_COUNT) {
            has_any = true;
            break;
        }
    }

    if (!has_any) {
        char *tname = mp_tprintf(20, "%s ", stream_type_name(filter));
        if (filter == STREAM_TYPE_COUNT)
            tname = "";
        MP_ERR(mpctx, "No %sstreams in file %s.\n", tname, disp_filename);
        goto err_out;
    }

    int first_num = -1;
    for (int n = 0; n < demux_get_num_stream(demuxer); n++) {
        struct sh_stream *sh = demux_get_stream(demuxer, n);
        struct track *t = add_stream_track(mpctx, demuxer, sh);
        t->is_external = true;
        if (sh->title && sh->title[0]) {
            t->title = talloc_strdup(t, sh->title);
        } else {
            t->title = talloc_strdup(t, mp_basename(disp_filename));
        }
        t->external_filename = talloc_strdup(t, filename);
        t->no_default = sh->type != filter;
        t->no_auto_select = t->no_default;
        if (first_num < 0 && (filter == STREAM_TYPE_COUNT || sh->type == filter))
            first_num = mpctx->num_tracks - 1;
    }

    mp_cancel_set_parent(demuxer->cancel, mpctx->playback_abort);

    return first_num;

err_out:
    demux_cancel_and_free(demuxer);
    if (!mp_cancel_test(cancel))
        MP_ERR(mpctx, "Can not open external file %s.\n", disp_filename);
    return -1;
}