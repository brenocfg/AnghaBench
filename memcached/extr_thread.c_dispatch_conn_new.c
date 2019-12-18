#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum network_transport { ____Placeholder_network_transport } network_transport ;
typedef  enum conn_states { ____Placeholder_conn_states } conn_states ;
struct TYPE_9__ {int num_threads; } ;
struct TYPE_8__ {int sfd; int init_state; int event_flags; int read_buffer_size; int transport; void* ssl; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  notify_send_fd; scalar_t__ thread_id; int /*<<< orphan*/  new_conn_queue; } ;
typedef  TYPE_1__ LIBEVENT_THREAD ;
typedef  TYPE_2__ CQ_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCACHED_CONN_DISPATCH (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cq_push (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* cqi_new () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int last_thread ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  queue_new_conn ; 
 TYPE_4__ settings ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* threads ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void dispatch_conn_new(int sfd, enum conn_states init_state, int event_flags,
                       int read_buffer_size, enum network_transport transport, void *ssl) {
    CQ_ITEM *item = cqi_new();
    char buf[1];
    if (item == NULL) {
        close(sfd);
        /* given that malloc failed this may also fail, but let's try */
        fprintf(stderr, "Failed to allocate memory for connection object\n");
        return ;
    }

    int tid = (last_thread + 1) % settings.num_threads;

    LIBEVENT_THREAD *thread = threads + tid;

    last_thread = tid;

    item->sfd = sfd;
    item->init_state = init_state;
    item->event_flags = event_flags;
    item->read_buffer_size = read_buffer_size;
    item->transport = transport;
    item->mode = queue_new_conn;
    item->ssl = ssl;

    cq_push(thread->new_conn_queue, item);

    MEMCACHED_CONN_DISPATCH(sfd, (int64_t)thread->thread_id);
    buf[0] = 'c';
    if (write(thread->notify_send_fd, buf, 1) != 1) {
        perror("Writing to thread notify pipe");
    }
}