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
struct MPContext {scalar_t__ stop_play; int /*<<< orphan*/  ao_filter_fmt; int /*<<< orphan*/ * ao; TYPE_1__* opts; } ;
struct TYPE_2__ {scalar_t__ gapless_audio; } ;

/* Variables and functions */
 scalar_t__ AT_END_OF_FILE ; 
 int /*<<< orphan*/  MPV_EVENT_AUDIO_RECONFIG ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ao_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ao_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void uninit_audio_out(struct MPContext *mpctx)
{
    if (mpctx->ao) {
        // Note: with gapless_audio, stop_play is not correctly set
        if (mpctx->opts->gapless_audio || mpctx->stop_play == AT_END_OF_FILE)
            ao_drain(mpctx->ao);
        ao_uninit(mpctx->ao);

        mp_notify(mpctx, MPV_EVENT_AUDIO_RECONFIG, NULL);
    }
    mpctx->ao = NULL;
    TA_FREEP(&mpctx->ao_filter_fmt);
}