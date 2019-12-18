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
struct ao_chain {int /*<<< orphan*/  filter; } ;
struct MPContext {double speed_factor_a; TYPE_1__* opts; struct ao_chain* ao_chain; } ;
struct TYPE_2__ {double playback_speed; int /*<<< orphan*/  pitch_correction; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_output_chain_set_audio_speed (int /*<<< orphan*/ ,double,double) ; 

__attribute__((used)) static void update_speed_filters(struct MPContext *mpctx)
{
    struct ao_chain *ao_c = mpctx->ao_chain;
    if (!ao_c)
        return;

    double speed = mpctx->opts->playback_speed;
    double resample = mpctx->speed_factor_a;

    if (!mpctx->opts->pitch_correction) {
        resample *= speed;
        speed = 1.0;
    }

    mp_output_chain_set_audio_speed(ao_c->filter, speed, resample);
}