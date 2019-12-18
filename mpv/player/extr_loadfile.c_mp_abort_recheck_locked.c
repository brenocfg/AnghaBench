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
struct mp_abort_entry {scalar_t__ coupled_to_playback; } ;
struct MPContext {scalar_t__ abort_all; int /*<<< orphan*/  playback_abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_abort_trigger_locked (struct MPContext*,struct mp_abort_entry*) ; 
 scalar_t__ mp_cancel_test (int /*<<< orphan*/ ) ; 

void mp_abort_recheck_locked(struct MPContext *mpctx,
                             struct mp_abort_entry *abort)
{
    if ((abort->coupled_to_playback && mp_cancel_test(mpctx->playback_abort)) ||
        mpctx->abort_all)
    {
        mp_abort_trigger_locked(mpctx, abort);
    }
}