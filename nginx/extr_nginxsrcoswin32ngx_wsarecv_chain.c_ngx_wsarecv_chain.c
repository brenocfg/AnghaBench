#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_13__ {int error; int eof; scalar_t__ ready; } ;
typedef  TYPE_2__ ngx_event_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; TYPE_2__* read; int /*<<< orphan*/  fd; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_15__ {struct TYPE_15__* next; TYPE_1__* buf; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_16__ {int size; int nalloc; scalar_t__ nelts; int /*<<< orphan*/ * elts; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_array_t ;
typedef  int /*<<< orphan*/  WSABUF ;
struct TYPE_17__ {size_t len; char* buf; } ;
struct TYPE_12__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * last; } ;
typedef  TYPE_6__* LPWSABUF ;

/* Variables and functions */
 size_t NGX_AGAIN ; 
 size_t NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int NGX_WSABUFS ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 int WSARecv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* ngx_array_push (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_3__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,size_t) ; 
 scalar_t__ ngx_socket_errno ; 

ssize_t
ngx_wsarecv_chain(ngx_connection_t *c, ngx_chain_t *chain, off_t limit)
{
    int           rc;
    u_char       *prev;
    u_long        bytes, flags;
    size_t        n, size;
    ngx_err_t     err;
    ngx_array_t   vec;
    ngx_event_t  *rev;
    LPWSABUF      wsabuf;
    WSABUF        wsabufs[NGX_WSABUFS];

    prev = NULL;
    wsabuf = NULL;
    flags = 0;
    size = 0;
    bytes = 0;

    vec.elts = wsabufs;
    vec.nelts = 0;
    vec.size = sizeof(WSABUF);
    vec.nalloc = NGX_WSABUFS;
    vec.pool = c->pool;

    /* coalesce the neighbouring bufs */

    while (chain) {
        n = chain->buf->end - chain->buf->last;

        if (limit) {
            if (size >= (size_t) limit) {
                break;
            }

            if (size + n > (size_t) limit) {
                n = (size_t) limit - size;
            }
        }

        if (prev == chain->buf->last) {
            wsabuf->len += n;

        } else {
            wsabuf = ngx_array_push(&vec);
            if (wsabuf == NULL) {
                return NGX_ERROR;
            }

            wsabuf->buf = (char *) chain->buf->last;
            wsabuf->len = n;
        }

        size += n;
        prev = chain->buf->end;
        chain = chain->next;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "WSARecv: %d:%d", vec.nelts, wsabuf->len);


    rc = WSARecv(c->fd, vec.elts, vec.nelts, &bytes, &flags, NULL, NULL);

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

    if (bytes < size) {
        rev->ready = 0;
    }

    if (bytes == 0) {
        rev->eof = 1;
    }

    return bytes;
}