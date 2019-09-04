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
struct MPContext {int audio_speed; int speed_factor_a; int video_speed; int speed_factor_v; TYPE_1__* opts; } ;
struct TYPE_2__ {int playback_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_speed_filters (struct MPContext*) ; 

void update_playback_speed(struct MPContext *mpctx)
{
    mpctx->audio_speed = mpctx->opts->playback_speed * mpctx->speed_factor_a;
    mpctx->video_speed = mpctx->opts->playback_speed * mpctx->speed_factor_v;

    update_speed_filters(mpctx);
}