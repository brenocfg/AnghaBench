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
struct MPContext {scalar_t__ stop_play; scalar_t__ initialized; } ;

/* Variables and functions */
 scalar_t__ PT_QUIT ; 
 int /*<<< orphan*/  mp_idle (struct MPContext*) ; 
 int /*<<< orphan*/  mp_play_files (struct MPContext*) ; 
 int /*<<< orphan*/  mp_shutdown_clients (struct MPContext*) ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 

__attribute__((used)) static void *core_thread(void *p)
{
    struct MPContext *mpctx = p;

    mpthread_set_name("mpv core");

    while (!mpctx->initialized && mpctx->stop_play != PT_QUIT)
        mp_idle(mpctx);

    if (mpctx->initialized)
        mp_play_files(mpctx);

    // This actually waits until all clients are gone before actually
    // destroying mpctx. Actual destruction is done by whatever destroys
    // the last mpv_handle.
    mp_shutdown_clients(mpctx);

    return NULL;
}