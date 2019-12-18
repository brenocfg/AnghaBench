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
struct mp_decoder_wrapper {int try_spdif; } ;
struct ao_chain {int spdif_failed; int spdif_passthrough; TYPE_1__* track; int /*<<< orphan*/  filter; } ;
struct MPContext {struct ao_chain* ao_chain; int /*<<< orphan*/  ao; } ;
struct TYPE_2__ {struct mp_decoder_wrapper* dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*) ; 
 int /*<<< orphan*/  ao_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_on_track (struct MPContext*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_decoder_wrapper_reinit (struct mp_decoder_wrapper*) ; 
 int /*<<< orphan*/  mp_output_chain_reset_harder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 
 int /*<<< orphan*/  reinit_audio_filters (struct MPContext*) ; 
 int /*<<< orphan*/  reset_audio_state (struct MPContext*) ; 
 int /*<<< orphan*/  uninit_audio_out (struct MPContext*) ; 

void reload_audio_output(struct MPContext *mpctx)
{
    if (!mpctx->ao)
        return;

    ao_reset(mpctx->ao);
    uninit_audio_out(mpctx);
    reinit_audio_filters(mpctx); // mostly to issue refresh seek

    struct ao_chain *ao_c = mpctx->ao_chain;

    if (ao_c) {
        reset_audio_state(mpctx);
        mp_output_chain_reset_harder(ao_c->filter);
    }

    // Whether we can use spdif might have changed. If we failed to use spdif
    // in the previous initialization, try it with spdif again (we'll fallback
    // to PCM again if necessary).
    if (ao_c && ao_c->track) {
        struct mp_decoder_wrapper *dec = ao_c->track->dec;
        if (dec && ao_c->spdif_failed) {
            ao_c->spdif_passthrough = true;
            ao_c->spdif_failed = false;
            dec->try_spdif = true;
            if (!mp_decoder_wrapper_reinit(dec)) {
                MP_ERR(mpctx, "Error reinitializing audio.\n");
                error_on_track(mpctx, ao_c->track);
            }
        }
    }

    mp_wakeup_core(mpctx);
}