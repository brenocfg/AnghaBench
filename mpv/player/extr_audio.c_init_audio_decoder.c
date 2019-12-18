#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct track {int /*<<< orphan*/ * sink; TYPE_1__* dec; scalar_t__ ao_c; int /*<<< orphan*/  stream; } ;
struct MPContext {int /*<<< orphan*/  filter_root; } ;
struct TYPE_3__ {int try_spdif; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error_on_track (struct MPContext*,struct track*) ; 
 TYPE_1__* mp_decoder_wrapper_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_decoder_wrapper_reinit (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_pin_disconnect (int /*<<< orphan*/ *) ; 

int init_audio_decoder(struct MPContext *mpctx, struct track *track)
{
    assert(!track->dec);
    if (!track->stream)
        goto init_error;

    track->dec = mp_decoder_wrapper_create(mpctx->filter_root, track->stream);
    if (!track->dec)
        goto init_error;

    if (track->ao_c)
        track->dec->try_spdif = true;

    if (!mp_decoder_wrapper_reinit(track->dec))
        goto init_error;

    return 1;

init_error:
    if (track->sink)
        mp_pin_disconnect(track->sink);
    track->sink = NULL;
    error_on_track(mpctx, track);
    return 0;
}