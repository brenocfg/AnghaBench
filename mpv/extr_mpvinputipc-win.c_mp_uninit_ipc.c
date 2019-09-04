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
struct mp_ipc_ctx {int /*<<< orphan*/  death_event; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct mp_ipc_ctx*) ; 

void mp_uninit_ipc(struct mp_ipc_ctx *arg)
{
    if (!arg)
        return;

    SetEvent(arg->death_event);
    pthread_join(arg->thread, NULL);

    CloseHandle(arg->death_event);
    talloc_free(arg);
}