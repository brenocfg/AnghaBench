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
struct demuxer_params {int stream_record; scalar_t__ demuxer_failed; int /*<<< orphan*/  stream_flags; int /*<<< orphan*/  force_format; } ;
struct MPContext {int /*<<< orphan*/  open_done; int /*<<< orphan*/  open_res_error; int /*<<< orphan*/  open_url; scalar_t__ open_res_demuxer; int /*<<< orphan*/  global; int /*<<< orphan*/  open_cancel; int /*<<< orphan*/  open_url_flags; int /*<<< orphan*/  open_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_ERROR_LOADING_FAILED ; 
 int /*<<< orphan*/  MPV_ERROR_UNKNOWN_FORMAT ; 
 int /*<<< orphan*/  MP_VERBOSE (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 scalar_t__ demux_open_url (int /*<<< orphan*/ ,struct demuxer_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 

__attribute__((used)) static void *open_demux_thread(void *ctx)
{
    struct MPContext *mpctx = ctx;

    mpthread_set_name("opener");

    struct demuxer_params p = {
        .force_format = mpctx->open_format,
        .stream_flags = mpctx->open_url_flags,
        .stream_record = true,
    };
    mpctx->open_res_demuxer =
        demux_open_url(mpctx->open_url, &p, mpctx->open_cancel, mpctx->global);

    if (mpctx->open_res_demuxer) {
        MP_VERBOSE(mpctx, "Opening done: %s\n", mpctx->open_url);
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