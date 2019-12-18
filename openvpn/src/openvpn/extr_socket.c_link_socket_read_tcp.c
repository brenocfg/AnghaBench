#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ residual_fully_formed; } ;
struct link_socket {int stream_reset; TYPE_1__ stream_buf; int /*<<< orphan*/  sd; int /*<<< orphan*/  reads; } ;
struct buffer {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLEN (struct buffer*) ; 
 int /*<<< orphan*/  BPTR (struct buffer*) ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket_finalize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct buffer*,int /*<<< orphan*/ *) ; 
 scalar_t__ stream_buf_added (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stream_buf_get_final (TYPE_1__*,struct buffer*) ; 
 int /*<<< orphan*/  stream_buf_get_next (TYPE_1__*,struct buffer*) ; 
 int /*<<< orphan*/  stream_buf_reset (TYPE_1__*) ; 

int
link_socket_read_tcp(struct link_socket *sock,
                     struct buffer *buf)
{
    int len = 0;

    if (!sock->stream_buf.residual_fully_formed)
    {
#ifdef _WIN32
        len = socket_finalize(sock->sd, &sock->reads, buf, NULL);
#else
        struct buffer frag;
        stream_buf_get_next(&sock->stream_buf, &frag);
        len = recv(sock->sd, BPTR(&frag), BLEN(&frag), MSG_NOSIGNAL);
#endif

        if (!len)
        {
            sock->stream_reset = true;
        }
        if (len <= 0)
        {
            return buf->len = len;
        }
    }

    if (sock->stream_buf.residual_fully_formed
        || stream_buf_added(&sock->stream_buf, len)) /* packet complete? */
    {
        stream_buf_get_final(&sock->stream_buf, buf);
        stream_buf_reset(&sock->stream_buf);
        return buf->len;
    }
    else
    {
        return buf->len = 0; /* no error, but packet is still incomplete */
    }
}