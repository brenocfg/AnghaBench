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
struct MPContext {scalar_t__ stop_play; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_abort_playback_async (struct MPContext*) ; 
 int /*<<< orphan*/  mp_hook_start (struct MPContext*,char*) ; 
 int /*<<< orphan*/  mp_hook_test_completion (struct MPContext*,char*) ; 
 int /*<<< orphan*/  mp_idle (struct MPContext*) ; 

__attribute__((used)) static void process_hooks(struct MPContext *mpctx, char *name)
{
    mp_hook_start(mpctx, name);

    while (!mp_hook_test_completion(mpctx, name)) {
        mp_idle(mpctx);

        // We have no idea what blocks a hook, so just do a full abort.
        if (mpctx->stop_play)
            mp_abort_playback_async(mpctx);
    }
}