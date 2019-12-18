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
struct MPContext {int /*<<< orphan*/  audio_status; int /*<<< orphan*/ * ao_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_AUDIO_RECONFIG ; 
 int /*<<< orphan*/  STATUS_EOF ; 
 int /*<<< orphan*/  ao_chain_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void uninit_audio_chain(struct MPContext *mpctx)
{
    if (mpctx->ao_chain) {
        ao_chain_uninit(mpctx->ao_chain);
        mpctx->ao_chain = NULL;

        mpctx->audio_status = STATUS_EOF;

        mp_notify(mpctx, MPV_EVENT_AUDIO_RECONFIG, NULL);
    }
}