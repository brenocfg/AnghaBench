#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sfd; TYPE_2__* thread; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ conn ;
struct TYPE_9__ {int /*<<< orphan*/  mode; TYPE_1__* c; int /*<<< orphan*/  init_state; int /*<<< orphan*/  sfd; } ;
struct TYPE_8__ {int /*<<< orphan*/  notify_send_fd; int /*<<< orphan*/  new_conn_queue; } ;
typedef  TYPE_2__ LIBEVENT_THREAD ;
typedef  TYPE_3__ CQ_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_closed ; 
 int /*<<< orphan*/  conn_new_cmd ; 
 int /*<<< orphan*/  cq_push (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* cqi_new () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  queue_redispatch ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void redispatch_conn(conn *c) {
    CQ_ITEM *item = cqi_new();
    char buf[1];
    if (item == NULL) {
        /* Can't cleanly redispatch connection. close it forcefully. */
        c->state = conn_closed;
        close(c->sfd);
        return;
    }
    LIBEVENT_THREAD *thread = c->thread;
    item->sfd = c->sfd;
    item->init_state = conn_new_cmd;
    item->c = c;
    item->mode = queue_redispatch;

    cq_push(thread->new_conn_queue, item);

    buf[0] = 'c';
    if (write(thread->notify_send_fd, buf, 1) != 1) {
        perror("Writing to thread notify pipe");
    }
}