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
struct track {struct sh_stream* stream; scalar_t__ dec; scalar_t__ d_sub; scalar_t__ selected; } ;
struct sh_stream {int dummy; } ;
struct mp_recorder_sink {int dummy; } ;
struct MPContext {int num_tracks; int /*<<< orphan*/  recorder; struct track** tracks; TYPE_1__* opts; int /*<<< orphan*/  global; int /*<<< orphan*/  playback_initialized; } ;
struct TYPE_2__ {char* record_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,struct sh_stream**,int,struct sh_stream*) ; 
 int /*<<< orphan*/  assert (struct mp_recorder_sink*) ; 
 int /*<<< orphan*/  close_recorder (struct MPContext*) ; 
 int /*<<< orphan*/  close_recorder_and_error (struct MPContext*) ; 
 int /*<<< orphan*/  mp_recorder_create (int /*<<< orphan*/ ,char*,struct sh_stream**,int) ; 
 struct mp_recorder_sink* mp_recorder_get_sink (int /*<<< orphan*/ ,struct sh_stream*) ; 
 int /*<<< orphan*/  mp_recorder_mark_discontinuity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_track_recorder_sink (struct track*,struct mp_recorder_sink*) ; 
 int /*<<< orphan*/  talloc_free (struct sh_stream**) ; 

void open_recorder(struct MPContext *mpctx, bool on_init)
{
    if (!mpctx->playback_initialized)
        return;

    close_recorder(mpctx);

    char *target = mpctx->opts->record_file;
    if (!target || !target[0])
        return;

    struct sh_stream **streams = NULL;
    int num_streams = 0;

    for (int n = 0; n < mpctx->num_tracks; n++) {
        struct track *track = mpctx->tracks[n];
        if (track->stream && track->selected && (track->d_sub || track->dec))
            MP_TARRAY_APPEND(NULL, streams, num_streams, track->stream);
    }

    mpctx->recorder = mp_recorder_create(mpctx->global, mpctx->opts->record_file,
                                         streams, num_streams);

    if (!mpctx->recorder) {
        talloc_free(streams);
        close_recorder_and_error(mpctx);
        return;
    }

    if (!on_init)
        mp_recorder_mark_discontinuity(mpctx->recorder);

    int n_stream = 0;
    for (int n = 0; n < mpctx->num_tracks; n++) {
        struct track *track = mpctx->tracks[n];
        if (n_stream >= num_streams)
            break;
        // (We expect track->stream not to be reused on other tracks.)
        if (track->stream == streams[n_stream]) {
            struct mp_recorder_sink * sink =
                mp_recorder_get_sink(mpctx->recorder, streams[n_stream]);
            assert(sink);
            set_track_recorder_sink(track, sink);
            n_stream++;
        }
    }

    talloc_free(streams);
}