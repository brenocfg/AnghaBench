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
struct sh_stream {int dummy; } ;
struct demuxer_params {int stream_record; int is_top_level; scalar_t__ demuxer_failed; int /*<<< orphan*/  stream_flags; int /*<<< orphan*/  force_format; } ;
struct demuxer {int /*<<< orphan*/  fully_read; } ;
struct MPContext {int /*<<< orphan*/  open_done; int /*<<< orphan*/  open_res_error; int /*<<< orphan*/  open_url; scalar_t__ open_for_prefetch; struct demuxer* open_res_demuxer; int /*<<< orphan*/  global; int /*<<< orphan*/  open_cancel; int /*<<< orphan*/  open_url_flags; int /*<<< orphan*/  open_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_ERROR_LOADING_FAILED ; 
 int /*<<< orphan*/  MPV_ERROR_UNKNOWN_FORMAT ; 
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int demux_get_num_stream (struct demuxer*) ; 
 struct sh_stream* demux_get_stream (struct demuxer*,int) ; 
 struct demuxer* demux_open_url (int /*<<< orphan*/ ,struct demuxer_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_set_wakeup_cb (struct demuxer*,int /*<<< orphan*/ ,struct MPContext*) ; 
 int /*<<< orphan*/  demux_start_prefetch (struct demuxer*) ; 
 int /*<<< orphan*/  demux_start_thread (struct demuxer*) ; 
 int /*<<< orphan*/  demuxer_select_track (struct demuxer*,struct sh_stream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 
 int /*<<< orphan*/  wakeup_demux ; 

__attribute__((used)) static void *open_demux_thread(void *ctx)
{
    struct MPContext *mpctx = ctx;

    mpthread_set_name("opener");

    struct demuxer_params p = {
        .force_format = mpctx->open_format,
        .stream_flags = mpctx->open_url_flags,
        .stream_record = true,
        .is_top_level = true,
    };
    struct demuxer *demux =
        demux_open_url(mpctx->open_url, &p, mpctx->open_cancel, mpctx->global);
    mpctx->open_res_demuxer = demux;

    if (demux) {
        MP_VERBOSE(mpctx, "Opening done: %s\n", mpctx->open_url);

        if (mpctx->open_for_prefetch && !demux->fully_read) {
            int num_streams = demux_get_num_stream(demux);
            for (int n = 0; n < num_streams; n++) {
                struct sh_stream *sh = demux_get_stream(demux, n);
                demuxer_select_track(demux, sh, MP_NOPTS_VALUE, true);
            }

            demux_set_wakeup_cb(demux, wakeup_demux, mpctx);
            demux_start_thread(demux);
            demux_start_prefetch(demux);
        }
    } else {
        MP_VERBOSE(mpctx, "Opening failed or was aborted: %s\n", mpctx->open_url);

        if (p.demuxer_failed) {
            mpctx->open_res_error = MPV_ERROR_UNKNOWN_FORMAT;
        } else {
            mpctx->open_res_error = MPV_ERROR_LOADING_FAILED;
        }
    }

    atomic_store(&mpctx->open_done, true);
    mp_wakeup_core(mpctx);
    return NULL;
}