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
struct mp_client_api {int shutting_down; int /*<<< orphan*/  lock; scalar_t__ terminate_core_thread; scalar_t__ num_clients; } ;
struct MPContext {scalar_t__ is_cli; scalar_t__ outstanding_async; struct mp_client_api* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_EVENT_SHUTDOWN ; 
 int /*<<< orphan*/  abort_async (struct MPContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_client_broadcast_event (struct MPContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_set_timeout (struct MPContext*,double) ; 
 double mp_time_sec () ; 
 int /*<<< orphan*/  mp_wait_events (struct MPContext*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mp_shutdown_clients(struct MPContext *mpctx)
{
    struct mp_client_api *clients = mpctx->clients;

    // Forcefully abort async work after 2 seconds of waiting.
    double abort_time = mp_time_sec() + 2;

    pthread_mutex_lock(&clients->lock);

    // Prevent that new clients can appear.
    clients->shutting_down = true;

    // Wait until we can terminate.
    while (clients->num_clients || mpctx->outstanding_async ||
           !(mpctx->is_cli || clients->terminate_core_thread))
    {
        pthread_mutex_unlock(&clients->lock);

        double left = abort_time - mp_time_sec();
        if (left >= 0) {
            mp_set_timeout(mpctx, left);
        } else {
            // Forcefully abort any ongoing async work. This is quite rude and
            // probably not what everyone wants, so it happens only after a
            // timeout.
            abort_async(mpctx, NULL, 0, 0);
        }

        mp_client_broadcast_event(mpctx, MPV_EVENT_SHUTDOWN, NULL);
        mp_wait_events(mpctx);

        pthread_mutex_lock(&clients->lock);
    }

    pthread_mutex_unlock(&clients->lock);
}