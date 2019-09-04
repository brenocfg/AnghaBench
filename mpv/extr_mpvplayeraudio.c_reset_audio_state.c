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
struct MPContext {scalar_t__ audio_stat_start; scalar_t__ audio_drop_throttle; scalar_t__ delay; scalar_t__ ao_chain; int /*<<< orphan*/  audio_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_EOF ; 
 int /*<<< orphan*/  STATUS_SYNCING ; 
 int /*<<< orphan*/  ao_chain_reset_state (scalar_t__) ; 

void reset_audio_state(struct MPContext *mpctx)
{
    if (mpctx->ao_chain)
        ao_chain_reset_state(mpctx->ao_chain);
    mpctx->audio_status = mpctx->ao_chain ? STATUS_SYNCING : STATUS_EOF;
    mpctx->delay = 0;
    mpctx->audio_drop_throttle = 0;
    mpctx->audio_stat_start = 0;
}