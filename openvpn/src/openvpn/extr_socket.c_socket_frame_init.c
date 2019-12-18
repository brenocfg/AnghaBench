#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  proto; } ;
struct TYPE_6__ {int /*<<< orphan*/  hEvent; } ;
struct TYPE_8__ {int /*<<< orphan*/  buf_init; TYPE_2__ overlapped; } ;
struct TYPE_5__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct link_socket {TYPE_3__ info; int /*<<< orphan*/  sockflags; int /*<<< orphan*/  stream_buf_data; int /*<<< orphan*/  stream_buf; TYPE_4__ reads; TYPE_4__ writes; TYPE_1__ rw_handle; } ;
struct frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FRAME_HEADROOM_MARKER_READ_STREAM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  alloc_buf_sock_tun (int /*<<< orphan*/ *,struct frame const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ link_socket_connection_oriented (struct link_socket*) ; 
 int /*<<< orphan*/  overlapped_io_init (TYPE_4__*,struct frame const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stream_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
socket_frame_init(const struct frame *frame, struct link_socket *sock)
{
#ifdef _WIN32
    overlapped_io_init(&sock->reads, frame, FALSE, false);
    overlapped_io_init(&sock->writes, frame, TRUE, false);
    sock->rw_handle.read = sock->reads.overlapped.hEvent;
    sock->rw_handle.write = sock->writes.overlapped.hEvent;
#endif

    if (link_socket_connection_oriented(sock))
    {
#ifdef _WIN32
        stream_buf_init(&sock->stream_buf,
                        &sock->reads.buf_init,
                        sock->sockflags,
                        sock->info.proto);
#else
        alloc_buf_sock_tun(&sock->stream_buf_data,
                           frame,
                           false,
                           FRAME_HEADROOM_MARKER_READ_STREAM);

        stream_buf_init(&sock->stream_buf,
                        &sock->stream_buf_data,
                        sock->sockflags,
                        sock->info.proto);
#endif
    }
}