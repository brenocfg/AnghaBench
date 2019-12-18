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
struct MPContext {TYPE_1__* opts; struct ao_chain* ao_chain; } ;
struct TYPE_2__ {int /*<<< orphan*/  af_settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_AUDIO_RECONFIG ; 
 int /*<<< orphan*/  MP_ERR (struct MPContext*,char*) ; 
 int /*<<< orphan*/  assert (struct ao_chain*) ; 
 int /*<<< orphan*/  mp_notify (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_output_chain_update_filters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_speed_filters (struct MPContext*) ; 

__attribute__((used)) static int recreate_audio_filters(struct MPContext *mpctx)
{
    struct ao_chain *ao_c = mpctx->ao_chain;
    assert(ao_c);

    if (!mp_output_chain_update_filters(ao_c->filter, mpctx->opts->af_settings))
        goto fail;

    update_speed_filters(mpctx);

    mp_notify(mpctx, MPV_EVENT_AUDIO_RECONFIG, NULL);

    return 0;

fail:
    MP_ERR(mpctx, "Audio filter initialized failed!\n");
    return -1;
}