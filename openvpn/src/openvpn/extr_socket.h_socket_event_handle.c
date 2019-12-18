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
struct link_socket {int /*<<< orphan*/ * sd; int /*<<< orphan*/  rw_handle; } ;
typedef  int /*<<< orphan*/ * event_t ;

/* Variables and functions */

__attribute__((used)) static inline event_t
socket_event_handle(const struct link_socket *s)
{
#ifdef _WIN32
    return &s->rw_handle;
#else
    return s->sd;
#endif
}