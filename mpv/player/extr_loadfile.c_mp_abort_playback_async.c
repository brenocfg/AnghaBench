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
struct MPContext {int num_abort_list; int /*<<< orphan*/  abort_lock; struct mp_abort_entry** abort_list; int /*<<< orphan*/  playback_abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_abort_trigger_locked (struct MPContext*,struct mp_abort_entry*) ; 
 int /*<<< orphan*/  mp_cancel_trigger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_abort_playback_async(struct MPContext *mpctx)
{
    mp_cancel_trigger(mpctx->playback_abort);

    pthread_mutex_lock(&mpctx->abort_lock);

    for (int n = 0; n < mpctx->num_abort_list; n++) {
        struct mp_abort_entry *abort = mpctx->abort_list[n];
        if (abort->coupled_to_playback)
            mp_abort_trigger_locked(mpctx, abort);
    }

    pthread_mutex_unlock(&mpctx->abort_lock);
}