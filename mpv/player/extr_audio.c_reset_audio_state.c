#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct track {TYPE_1__* dec; } ;
struct MPContext {scalar_t__ audio_stat_start; scalar_t__ audio_drop_throttle; scalar_t__ delay; TYPE_2__* ao_chain; int /*<<< orphan*/  audio_status; int /*<<< orphan*/  play_dir; } ;
struct TYPE_4__ {struct track* track; } ;
struct TYPE_3__ {int /*<<< orphan*/  play_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_EOF ; 
 int /*<<< orphan*/  STATUS_SYNCING ; 
 int /*<<< orphan*/  ao_chain_reset_state (TYPE_2__*) ; 

void reset_audio_state(struct MPContext *mpctx)
{
    if (mpctx->ao_chain) {
        ao_chain_reset_state(mpctx->ao_chain);
        struct track *t = mpctx->ao_chain->track;
        if (t && t->dec)
            t->dec->play_dir = mpctx->play_dir;
    }
    mpctx->audio_status = mpctx->ao_chain ? STATUS_SYNCING : STATUS_EOF;
    mpctx->delay = 0;
    mpctx->audio_drop_throttle = 0;
    mpctx->audio_stat_start = 0;
}