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
struct link_socket {int dummy; } ;

/* Variables and functions */
 scalar_t__ link_socket_connection_oriented (struct link_socket*) ; 
 int stream_buf_read_setup_dowork (struct link_socket*) ; 

__attribute__((used)) static inline bool
stream_buf_read_setup(struct link_socket *sock)
{
    if (link_socket_connection_oriented(sock))
    {
        return stream_buf_read_setup_dowork(sock);
    }
    else
    {
        return true;
    }
}