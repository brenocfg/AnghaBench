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
struct link_socket {int /*<<< orphan*/ * sd; int /*<<< orphan*/  listen_handle; } ;
typedef  int /*<<< orphan*/ * event_t ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ACCEPT ; 
 int /*<<< orphan*/  defined_net_event_win32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net_event_win32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

event_t
socket_listen_event_handle(struct link_socket *s)
{
#ifdef _WIN32
    if (!defined_net_event_win32(&s->listen_handle))
    {
        init_net_event_win32(&s->listen_handle, FD_ACCEPT, s->sd, 0);
    }
    return &s->listen_handle;
#else  /* ifdef _WIN32 */
    return s->sd;
#endif
}