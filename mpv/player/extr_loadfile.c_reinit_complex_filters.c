#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct vo_chain {struct mp_pin* filter_src; TYPE_3__* filter; struct track* track; } ;
struct track {int type; int user_tid; int selected; TYPE_7__* dec; struct mp_pin* sink; } ;
struct mp_pin {int dummy; } ;
struct mp_lavfi {TYPE_8__* f; } ;
struct ao_chain {struct mp_pin* filter_src; TYPE_5__* filter; struct track* track; } ;
struct MPContext {int num_tracks; struct track** tracks; scalar_t__ playback_initialized; TYPE_8__* lavfi; struct ao_chain* ao_chain; struct vo_chain* vo_chain; int /*<<< orphan*/  filter_root; int /*<<< orphan*/  lavfi_graph; TYPE_1__* opts; } ;
typedef  int /*<<< orphan*/  label ;
struct TYPE_18__ {int num_pins; struct mp_pin** pins; } ;
struct TYPE_17__ {TYPE_6__* f; } ;
struct TYPE_16__ {struct mp_pin** pins; } ;
struct TYPE_15__ {TYPE_4__* f; } ;
struct TYPE_14__ {struct mp_pin** pins; } ;
struct TYPE_13__ {TYPE_2__* f; } ;
struct TYPE_12__ {struct mp_pin** pins; } ;
struct TYPE_11__ {char* lavfi_complex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_TRACKS_CHANGED ; 
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MP_PIN_IN ; 
 scalar_t__ MP_PIN_OUT ; 
#define  STREAM_AUDIO 129 
#define  STREAM_VIDEO 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cleanup_deassociated_complex_filters (struct MPContext*) ; 
 int /*<<< orphan*/  deassociate_complex_filters (struct MPContext*) ; 
 int /*<<< orphan*/  init_audio_decoder (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  init_video_decoder (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  kill_outputs (struct MPContext*,struct track*) ; 
 struct mp_pin* mp_filter_get_named_pin (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  mp_filter_has_failed (TYPE_8__*) ; 
 int /*<<< orphan*/  mp_filter_set_error_handler (TYPE_8__*,int /*<<< orphan*/ ) ; 
 struct mp_lavfi* mp_lavfi_create_graph (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_pin_connect (struct mp_pin*,struct mp_pin*) ; 
 int /*<<< orphan*/  mp_pin_disconnect (struct mp_pin*) ; 
 scalar_t__ mp_pin_get_dir (struct mp_pin*) ; 
 int /*<<< orphan*/  mp_pin_get_name (struct mp_pin*) ; 
 int /*<<< orphan*/  mp_pin_is_connected (struct mp_pin*) ; 
 int /*<<< orphan*/  reinit_audio_chain_src (struct MPContext*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_video_chain_src (struct MPContext*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reselect_demux_stream (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_strdup (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int reinit_complex_filters(struct MPContext *mpctx, bool force_uninit)
{
    char *graph = mpctx->opts->lavfi_complex;
    bool have_graph = graph && graph[0] && !force_uninit;
    if (have_graph && mpctx->lavfi &&
        strcmp(graph, mpctx->lavfi_graph) == 0 &&
        !mp_filter_has_failed(mpctx->lavfi))
        return 0;
    if (!mpctx->lavfi && !have_graph)
        return 0;

    // Deassociate the old filter pads. We leave both sources (tracks) and
    // sinks (AO/VO) "dangling", connected to neither track or filter pad.
    // Later, we either reassociate them with new pads, or uninit them if
    // they are still dangling. This avoids too interruptive actions like
    // recreating the VO.
    deassociate_complex_filters(mpctx);

    bool success = false;
    if (!have_graph) {
        success = true; // normal full removal of graph
        goto done;
    }

    struct mp_lavfi *l =
        mp_lavfi_create_graph(mpctx->filter_root, 0, false, NULL, graph);
    if (!l)
        goto done;
    mpctx->lavfi = l->f;
    mpctx->lavfi_graph = talloc_strdup(NULL, graph);

    mp_filter_set_error_handler(mpctx->lavfi, mpctx->filter_root);

    for (int n = 0; n < mpctx->lavfi->num_pins; n++)
        mp_pin_disconnect(mpctx->lavfi->pins[n]);

    struct mp_pin *pad = mp_filter_get_named_pin(mpctx->lavfi, "vo");
    if (pad && mp_pin_get_dir(pad) == MP_PIN_OUT) {
        if (mpctx->vo_chain && mpctx->vo_chain->track)
            kill_outputs(mpctx, mpctx->vo_chain->track);
        if (!mpctx->vo_chain) {
            reinit_video_chain_src(mpctx, NULL);
            if (!mpctx->vo_chain)
                goto done;
        }
        struct vo_chain *vo_c = mpctx->vo_chain;
        assert(!vo_c->track);
        vo_c->filter_src = pad;
        mp_pin_connect(vo_c->filter->f->pins[0], vo_c->filter_src);
    }

    pad = mp_filter_get_named_pin(mpctx->lavfi, "ao");
    if (pad && mp_pin_get_dir(pad) == MP_PIN_OUT) {
        if (mpctx->ao_chain && mpctx->ao_chain->track)
            kill_outputs(mpctx, mpctx->ao_chain->track);
        if (!mpctx->ao_chain) {
            reinit_audio_chain_src(mpctx, NULL);
            if (!mpctx->ao_chain)
                goto done;
        }
        struct ao_chain *ao_c = mpctx->ao_chain;
        assert(!ao_c->track);
        ao_c->filter_src = pad;
        mp_pin_connect(ao_c->filter->f->pins[0], ao_c->filter_src);
    }

    for (int n = 0; n < mpctx->num_tracks; n++) {
        struct track *track = mpctx->tracks[n];

        char label[32];
        char prefix;
        switch (track->type) {
        case STREAM_VIDEO: prefix = 'v'; break;
        case STREAM_AUDIO: prefix = 'a'; break;
        default: continue;
        }
        snprintf(label, sizeof(label), "%cid%d", prefix, track->user_tid);

        pad = mp_filter_get_named_pin(mpctx->lavfi, label);
        if (!pad)
            continue;
        if (mp_pin_get_dir(pad) != MP_PIN_IN)
            continue;
        assert(!mp_pin_is_connected(pad));

        assert(!track->sink);

        kill_outputs(mpctx, track);

        track->sink = pad;
        track->selected = true;

        if (!track->dec) {
            if (track->type == STREAM_VIDEO && !init_video_decoder(mpctx, track))
                goto done;
            if (track->type == STREAM_AUDIO && !init_audio_decoder(mpctx, track))
                goto done;
        }

        mp_pin_connect(track->sink, track->dec->f->pins[0]);
    }

    // Don't allow unconnected pins. Libavfilter would make the data flow a
    // real pain anyway.
    for (int n = 0; n < mpctx->lavfi->num_pins; n++) {
        struct mp_pin *pin = mpctx->lavfi->pins[n];
        if (!mp_pin_is_connected(pin)) {
            MP_ERR(mpctx, "Pad %s is not connected to anything.\n",
                   mp_pin_get_name(pin));
            goto done;
        }
    }

    success = true;
done:

    if (!success)
        deassociate_complex_filters(mpctx);

    cleanup_deassociated_complex_filters(mpctx);

    if (mpctx->playback_initialized) {
        for (int n = 0; n < mpctx->num_tracks; n++)
            reselect_demux_stream(mpctx, mpctx->tracks[n]);
    }

    mp_notify(mpctx, MPV_EVENT_TRACKS_CHANGED, NULL);

    return success ? 1 : -1;
}