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
typedef  scalar_t__ uint64_t ;
struct mp_abort_entry {int client_work_type; scalar_t__ client_work_id; int /*<<< orphan*/ * client; } ;
struct MPContext {int abort_all; int num_abort_list; int /*<<< orphan*/  abort_lock; struct mp_abort_entry** abort_list; } ;
typedef  int /*<<< orphan*/  mpv_handle ;

/* Variables and functions */
 int /*<<< orphan*/  mp_abort_trigger_locked (struct MPContext*,struct mp_abort_entry*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void abort_async(struct MPContext *mpctx, mpv_handle *ctx,
                        int type, uint64_t id)
{
    pthread_mutex_lock(&mpctx->abort_lock);

    // Destroy all => ensure any newly appearing work is aborted immediately.
    if (ctx == NULL)
        mpctx->abort_all = true;

    for (int n = 0; n < mpctx->num_abort_list; n++) {
        struct mp_abort_entry *abort = mpctx->abort_list[n];
        if (!ctx || (abort->client == ctx && (!type ||
            (abort->client_work_type == type && abort->client_work_id == id))))
        {
            mp_abort_trigger_locked(mpctx, abort);
        }
    }

    pthread_mutex_unlock(&mpctx->abort_lock);
}