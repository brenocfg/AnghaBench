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
struct link_socket_addr {int /*<<< orphan*/ * current_remote; int /*<<< orphan*/ * remote_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  freeaddrinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clear_remote_addrlist(struct link_socket_addr *lsa, bool free)
{
    if (lsa->remote_list && free)
    {
        freeaddrinfo(lsa->remote_list);
    }
    lsa->remote_list = NULL;
    lsa->current_remote = NULL;
}