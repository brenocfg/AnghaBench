#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ off_t ;
struct TYPE_18__ {scalar_t__ error; } ;
struct TYPE_19__ {int ready; int active; int error; scalar_t__ available; TYPE_1__ ovlp; scalar_t__ complete; } ;
typedef  TYPE_2__ ngx_event_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_20__ {int /*<<< orphan*/  sent; int /*<<< orphan*/  fd; int /*<<< orphan*/  log; TYPE_2__* write; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_21__ {TYPE_13__* buf; struct TYPE_21__* next; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_22__ {scalar_t__ nelts; int size; int nalloc; int /*<<< orphan*/ * elts; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_array_t ;
typedef  int /*<<< orphan*/  WSAOVERLAPPED ;
typedef  int /*<<< orphan*/  WSABUF ;
struct TYPE_23__ {int len; char* buf; } ;
struct TYPE_17__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  scalar_t__ LPWSAOVERLAPPED ;
typedef  TYPE_6__* LPWSABUF ;

/* Variables and functions */
 TYPE_4__* NGX_CHAIN_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ NGX_MAX_UINT32_VALUE ; 
 int NGX_USE_IOCP_EVENT ; 
 int NGX_WSABUFS ; 
 scalar_t__ WSAGetOverlappedResult (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int WSASend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ WSA_IO_PENDING ; 
 TYPE_6__* ngx_array_push (TYPE_5__*) ; 
 scalar_t__ ngx_buf_special (TYPE_13__*) ; 
 TYPE_4__* ngx_chain_update_sent (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_3__*,scalar_t__,char*) ; 
 scalar_t__ ngx_errno ; 
 int ngx_event_flags ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_max_wsabufs ; 
 int /*<<< orphan*/  ngx_memzero (scalar_t__,int) ; 
 scalar_t__ ngx_pagesize ; 
 scalar_t__ ngx_socket_errno ; 

ngx_chain_t *
ngx_overlapped_wsasend_chain(ngx_connection_t *c, ngx_chain_t *in, off_t limit)
{
    int               rc;
    u_char           *prev;
    u_long            size, send, sent;
    ngx_err_t         err;
    ngx_event_t      *wev;
    ngx_array_t       vec;
    ngx_chain_t      *cl;
    LPWSAOVERLAPPED   ovlp;
    LPWSABUF          wsabuf;
    WSABUF            wsabufs[NGX_WSABUFS];

    wev = c->write;

    if (!wev->ready) {
        return in;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "wev->complete: %d", wev->complete);

    if (!wev->complete) {

        /* post the overlapped WSASend() */

        /* the maximum limit size is the maximum u_long value - the page size */

        if (limit == 0 || limit > (off_t) (NGX_MAX_UINT32_VALUE - ngx_pagesize))
        {
            limit = NGX_MAX_UINT32_VALUE - ngx_pagesize;
        }

        /*
         * WSABUFs must be 4-byte aligned otherwise
         * WSASend() will return undocumented WSAEINVAL error.
         */

        vec.elts = wsabufs;
        vec.nelts = 0;
        vec.size = sizeof(WSABUF);
        vec.nalloc = NGX_WSABUFS;
        vec.pool = c->pool;

        send = 0;
        prev = NULL;
        wsabuf = NULL;

        /* create the WSABUF and coalesce the neighbouring bufs */

        for (cl = in;
             cl && vec.nelts < ngx_max_wsabufs && send < limit;
             cl = cl->next)
        {
            if (ngx_buf_special(cl->buf)) {
                continue;
            }

            size = cl->buf->last - cl->buf->pos;

            if (send + size > limit) {
                size = (u_long) (limit - send);
            }

            if (prev == cl->buf->pos) {
                wsabuf->len += cl->buf->last - cl->buf->pos;

            } else {
                wsabuf = ngx_array_push(&vec);
                if (wsabuf == NULL) {
                    return NGX_CHAIN_ERROR;
                }

                wsabuf->buf = (char *) cl->buf->pos;
                wsabuf->len = cl->buf->last - cl->buf->pos;
            }

            prev = cl->buf->last;
            send += size;
        }

        ovlp = (LPWSAOVERLAPPED) &c->write->ovlp;
        ngx_memzero(ovlp, sizeof(WSAOVERLAPPED));

        rc = WSASend(c->fd, vec.elts, vec.nelts, &sent, 0, ovlp, NULL);

        wev->complete = 0;

        if (rc == -1) {
            err = ngx_errno;

            if (err == WSA_IO_PENDING) {
                ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, err,
                               "WSASend() posted");
                wev->active = 1;
                return in;

            } else {
                wev->error = 1;
                ngx_connection_error(c, err, "WSASend() failed");
                return NGX_CHAIN_ERROR;
            }

        } else if (ngx_event_flags & NGX_USE_IOCP_EVENT) {

            /*
             * if a socket was bound with I/O completion port then
             * GetQueuedCompletionStatus() would anyway return its status
             * despite that WSASend() was already complete
             */

            wev->active = 1;
            return in;
        }

        ngx_log_debug2(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "WSASend: fd:%d, s:%ul", c->fd, sent);

    } else {

        /* the overlapped WSASend() complete */

        wev->complete = 0;
        wev->active = 0;

        if (ngx_event_flags & NGX_USE_IOCP_EVENT) {
            if (wev->ovlp.error) {
                ngx_connection_error(c, wev->ovlp.error, "WSASend() failed");
                return NGX_CHAIN_ERROR;
            }

            sent = wev->available;

        } else {
            if (WSAGetOverlappedResult(c->fd, (LPWSAOVERLAPPED) &wev->ovlp,
                                       &sent, 0, NULL)
                == 0)
            {
                ngx_connection_error(c, ngx_socket_errno,
                               "WSASend() or WSAGetOverlappedResult() failed");

                return NGX_CHAIN_ERROR;
            }
        }
    }

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "WSASend ovlp: fd:%d, s:%ul", c->fd, sent);

    c->sent += sent;

    in = ngx_chain_update_sent(in, sent);

    if (in) {
        wev->ready = 0;

    } else {
        wev->ready = 1;
    }

    return in;
}