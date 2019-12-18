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
struct link_socket {unsigned int rwflags_debug; } ;
struct event_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int EVENT_READ ; 
 int /*<<< orphan*/  event_ctl (struct event_set*,int /*<<< orphan*/ ,unsigned int,void*) ; 
 int /*<<< orphan*/  socket_event_handle (struct link_socket*) ; 
 int /*<<< orphan*/  socket_recv_queue (struct link_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_buf_read_setup (struct link_socket*) ; 

unsigned int
socket_set(struct link_socket *s,
           struct event_set *es,
           unsigned int rwflags,
           void *arg,
           unsigned int *persistent)
{
    if (s)
    {
        if ((rwflags & EVENT_READ) && !stream_buf_read_setup(s))
        {
            ASSERT(!persistent);
            rwflags &= ~EVENT_READ;
        }

#ifdef _WIN32
        if (rwflags & EVENT_READ)
        {
            socket_recv_queue(s, 0);
        }
#endif

        /* if persistent is defined, call event_ctl only if rwflags has changed since last call */
        if (!persistent || *persistent != rwflags)
        {
            event_ctl(es, socket_event_handle(s), rwflags, arg);
            if (persistent)
            {
                *persistent = rwflags;
            }
        }

        s->rwflags_debug = rwflags;
    }
    return rwflags;
}