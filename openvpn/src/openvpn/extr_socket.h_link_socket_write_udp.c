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
struct link_socket {int dummy; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 size_t link_socket_write_udp_posix (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 
 size_t link_socket_write_win32 (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 

__attribute__((used)) static inline size_t
link_socket_write_udp(struct link_socket *sock,
                      struct buffer *buf,
                      struct link_socket_actual *to)
{
#ifdef _WIN32
    return link_socket_write_win32(sock, buf, to);
#else
    return link_socket_write_udp_posix(sock, buf, to);
#endif
}