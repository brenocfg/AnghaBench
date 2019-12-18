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
struct link_socket {int /*<<< orphan*/  sd; int /*<<< orphan*/  listen_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_net_event_win32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
socket_reset_listen_persistent(struct link_socket *s)
{
#ifdef _WIN32
    reset_net_event_win32(&s->listen_handle, s->sd);
#endif
}