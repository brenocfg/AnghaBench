#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pfd; scalar_t__ batch_pos; scalar_t__ batch_len; int /*<<< orphan*/ * batch; scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct nn_usock {int s; int /*<<< orphan*/ * asock; int /*<<< orphan*/  event_error; int /*<<< orphan*/  event_received; int /*<<< orphan*/  event_sent; int /*<<< orphan*/  event_established; int /*<<< orphan*/  fsm; int /*<<< orphan*/  task_stop; int /*<<< orphan*/  task_recv; int /*<<< orphan*/  task_send; int /*<<< orphan*/  task_accept; int /*<<< orphan*/  task_connected; int /*<<< orphan*/  task_connecting; int /*<<< orphan*/  wfd; TYPE_2__ out; TYPE_1__ in; scalar_t__ errnum; int /*<<< orphan*/  worker; int /*<<< orphan*/  state; } ;
struct nn_fsm {int dummy; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_USOCK_SRC_FD ; 
 int /*<<< orphan*/  NN_USOCK_SRC_TASK_ACCEPT ; 
 int /*<<< orphan*/  NN_USOCK_SRC_TASK_CONNECTED ; 
 int /*<<< orphan*/  NN_USOCK_SRC_TASK_CONNECTING ; 
 int /*<<< orphan*/  NN_USOCK_SRC_TASK_RECV ; 
 int /*<<< orphan*/  NN_USOCK_SRC_TASK_SEND ; 
 int /*<<< orphan*/  NN_USOCK_SRC_TASK_STOP ; 
 int /*<<< orphan*/  NN_USOCK_STATE_IDLE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_fsm_choose_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nn_usock*,struct nn_fsm*) ; 
 int /*<<< orphan*/  nn_usock_handler ; 
 int /*<<< orphan*/  nn_usock_shutdown ; 
 int /*<<< orphan*/  nn_worker_fd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_task_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_usock_init (struct nn_usock *self, int src, struct nn_fsm *owner)
{
    /*  Initalise the state machine. */
    nn_fsm_init (&self->fsm, nn_usock_handler, nn_usock_shutdown,
        src, self, owner);
    self->state = NN_USOCK_STATE_IDLE;

    /*  Choose a worker thread to handle this socket. */
    self->worker = nn_fsm_choose_worker (&self->fsm);

    /*  Actual file descriptor will be generated during 'start' step. */
    self->s = -1;
    self->errnum = 0;

    self->in.buf = NULL;
    self->in.len = 0;
    self->in.batch = NULL;
    self->in.batch_len = 0;
    self->in.batch_pos = 0;
    self->in.pfd = NULL;

    memset (&self->out.hdr, 0, sizeof (struct msghdr));

    /*  Initialise tasks for the worker thread. */
    nn_worker_fd_init (&self->wfd, NN_USOCK_SRC_FD, &self->fsm);
    nn_worker_task_init (&self->task_connecting, NN_USOCK_SRC_TASK_CONNECTING,
        &self->fsm);
    nn_worker_task_init (&self->task_connected, NN_USOCK_SRC_TASK_CONNECTED,
        &self->fsm);
    nn_worker_task_init (&self->task_accept, NN_USOCK_SRC_TASK_ACCEPT,
        &self->fsm);
    nn_worker_task_init (&self->task_send, NN_USOCK_SRC_TASK_SEND, &self->fsm);
    nn_worker_task_init (&self->task_recv, NN_USOCK_SRC_TASK_RECV, &self->fsm);
    nn_worker_task_init (&self->task_stop, NN_USOCK_SRC_TASK_STOP, &self->fsm);

    /*  Intialise events raised by usock. */
    nn_fsm_event_init (&self->event_established);
    nn_fsm_event_init (&self->event_sent);
    nn_fsm_event_init (&self->event_received);
    nn_fsm_event_init (&self->event_error);

    /*  accepting is not going on at the moment. */
    self->asock = NULL;
}