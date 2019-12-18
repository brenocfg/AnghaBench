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
struct TYPE_2__ {int /*<<< orphan*/  head; } ;
struct mp_cancel {scalar_t__* wakeup_pipe; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  lock; scalar_t__ win32_event; TYPE_1__ slaves; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  mp_cancel_set_parent (struct mp_cancel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cancel_destroy(void *p)
{
    struct mp_cancel *c = p;

    assert(!c->slaves.head); // API user error

    mp_cancel_set_parent(c, NULL);

    if (c->wakeup_pipe[0] >= 0) {
        close(c->wakeup_pipe[0]);
        close(c->wakeup_pipe[1]);
    }

#ifdef __MINGW32__
    if (c->win32_event)
        CloseHandle(c->win32_event);
#endif

    pthread_mutex_destroy(&c->lock);
    pthread_cond_destroy(&c->wakeup);
}