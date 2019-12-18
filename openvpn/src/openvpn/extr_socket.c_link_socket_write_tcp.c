#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct link_socket_actual {int dummy; } ;
struct TYPE_2__ {scalar_t__ maxlen; } ;
struct link_socket {TYPE_1__ stream_buf; } ;
struct buffer {int /*<<< orphan*/  offset; } ;
typedef  scalar_t__ packet_size_type ;
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BLEN (struct buffer*) ; 
 int /*<<< orphan*/  D_STREAM_DEBUG ; 
 int buf_write_prepend (struct buffer*,scalar_t__*,int) ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ htonps (scalar_t__) ; 
 int link_socket_write_tcp_posix (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 
 int link_socket_write_win32 (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 

int
link_socket_write_tcp(struct link_socket *sock,
                      struct buffer *buf,
                      struct link_socket_actual *to)
{
    packet_size_type len = BLEN(buf);
    dmsg(D_STREAM_DEBUG, "STREAM: WRITE %d offset=%d", (int)len, buf->offset);
    ASSERT(len <= sock->stream_buf.maxlen);
    len = htonps(len);
    ASSERT(buf_write_prepend(buf, &len, sizeof(len)));
#ifdef _WIN32
    return link_socket_write_win32(sock, buf, to);
#else
    return link_socket_write_tcp_posix(sock, buf, to);
#endif
}