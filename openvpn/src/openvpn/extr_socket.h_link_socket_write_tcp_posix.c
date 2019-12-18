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
struct link_socket_actual {int dummy; } ;
struct link_socket {int /*<<< orphan*/  sd; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLEN (struct buffer*) ; 
 int /*<<< orphan*/  BPTR (struct buffer*) ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 size_t send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t
link_socket_write_tcp_posix(struct link_socket *sock,
                            struct buffer *buf,
                            struct link_socket_actual *to)
{
    return send(sock->sd, BPTR(buf), BLEN(buf), MSG_NOSIGNAL);
}