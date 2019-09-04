#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {int error; scalar_t__ ready; } ;
typedef  TYPE_1__ ngx_event_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; TYPE_1__* read; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ ngx_connection_t ;
struct TYPE_9__ {char* buf; size_t len; } ;
typedef  TYPE_3__ WSABUF ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 int WSARecv (int /*<<< orphan*/ ,TYPE_3__*,int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,scalar_t__,size_t) ; 
 scalar_t__ ngx_socket_errno ; 

ssize_t
ngx_udp_wsarecv(ngx_connection_t *c, u_char *buf, size_t size)
{
    int           rc;
    u_long        bytes, flags;
    WSABUF        wsabuf[1];
    ngx_err_t     err;
    ngx_event_t  *rev;

    wsabuf[0].buf = (char *) buf;
    wsabuf[0].len = size;
    flags = 0;
    bytes = 0;

    rc = WSARecv(c->fd, wsabuf, 1, &bytes, &flags, NULL, NULL);

    ngx_log_debug4(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "WSARecv: fd:%d rc:%d %ul of %z", c->fd, rc, bytes, size);

    rev = c->read;

    if (rc == -1) {
        rev->ready = 0;
        err = ngx_socket_errno;

        if (err == WSAEWOULDBLOCK) {
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, err,
                           "WSARecv() not ready");
            return NGX_AGAIN;
        }

        rev->error = 1;
        ngx_connection_error(c, err, "WSARecv() failed");

        return NGX_ERROR;
    }

    return bytes;
}