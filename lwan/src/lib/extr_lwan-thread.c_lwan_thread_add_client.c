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
struct lwan_thread {int /*<<< orphan*/  pending_fds; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lwan_status_error (char*,int) ; 
 int /*<<< orphan*/  lwan_thread_nudge (struct lwan_thread*) ; 
 int spsc_queue_push (int /*<<< orphan*/ *,int) ; 

void lwan_thread_add_client(struct lwan_thread *t, int fd)
{
    for (int i = 0; i < 10; i++) {
        bool pushed = spsc_queue_push(&t->pending_fds, fd);

        if (LIKELY(pushed))
            return;

        /* Queue is full; nudge the thread to consume it. */
        lwan_thread_nudge(t);
    }

    lwan_status_error("Dropping connection %d", fd);
    /* FIXME: send "busy" response now, even without receiving request? */
    close(fd);
}