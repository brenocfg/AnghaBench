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
struct gc_arena {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  socket_descriptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct addrinfo const*) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_sockaddr (int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  set_nonblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
socket_do_listen(socket_descriptor_t sd,
                 const struct addrinfo *local,
                 bool do_listen,
                 bool do_set_nonblock)
{
    struct gc_arena gc = gc_new();
    if (do_listen)
    {
        ASSERT(local);
        msg(M_INFO, "Listening for incoming TCP connection on %s",
            print_sockaddr(local->ai_addr, &gc));
        if (listen(sd, 32))
        {
            msg(M_ERR, "TCP: listen() failed");
        }
    }

    /* set socket to non-blocking mode */
    if (do_set_nonblock)
    {
        set_nonblock(sd);
    }

    gc_free(&gc);
}