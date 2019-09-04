#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
struct TYPE_23__ {size_t sfv_len; int sfv_fd; scalar_t__ sfv_off; scalar_t__ sfv_flag; } ;
typedef  TYPE_3__ sendfilevec_t ;
typedef  scalar_t__ off_t ;
typedef  int ngx_uint_t ;
typedef  int ngx_int_t ;
struct TYPE_24__ {int error; scalar_t__ ready; } ;
typedef  TYPE_4__ ngx_event_t ;
typedef  int ngx_err_t ;
struct TYPE_25__ {size_t sent; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; int /*<<< orphan*/  sendfile; TYPE_4__* write; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_26__ {TYPE_7__* buf; struct TYPE_26__* next; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_27__ {int last; scalar_t__ pos; scalar_t__ file_last; scalar_t__ file_pos; TYPE_2__* file; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
struct TYPE_22__ {int fd; TYPE_1__ name; } ;

/* Variables and functions */
 TYPE_6__* NGX_CHAIN_ERROR ; 
#define  NGX_EAGAIN 129 
#define  NGX_EINTR 128 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ NGX_MAX_SIZE_T_VALUE ; 
 int NGX_SENDFILEVECS ; 
 void* SFV_FD_SELF ; 
 scalar_t__ ngx_buf_in_memory_only (TYPE_7__*) ; 
 scalar_t__ ngx_buf_special (TYPE_7__*) ; 
 TYPE_6__* ngx_chain_update_sent (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_5__*,int,char*) ; 
 int ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_pagesize ; 
 TYPE_6__* ngx_writev_chain (TYPE_5__*,TYPE_6__*,scalar_t__) ; 
 int sendfilev (int /*<<< orphan*/ ,TYPE_3__*,int,size_t*) ; 

ngx_chain_t *
ngx_solaris_sendfilev_chain(ngx_connection_t *c, ngx_chain_t *in, off_t limit)
{
    int             fd;
    u_char         *prev;
    off_t           size, send, prev_send, aligned, fprev;
    size_t          sent;
    ssize_t         n;
    ngx_int_t       eintr;
    ngx_err_t       err;
    ngx_buf_t      *file;
    ngx_uint_t      nsfv;
    sendfilevec_t  *sfv, sfvs[NGX_SENDFILEVECS];
    ngx_event_t    *wev;
    ngx_chain_t    *cl;

    wev = c->write;

    if (!wev->ready) {
        return in;
    }

    if (!c->sendfile) {
        return ngx_writev_chain(c, in, limit);
    }


    /* the maximum limit size is the maximum size_t value - the page size */

    if (limit == 0 || limit > (off_t) (NGX_MAX_SIZE_T_VALUE - ngx_pagesize)) {
        limit = NGX_MAX_SIZE_T_VALUE - ngx_pagesize;
    }


    send = 0;

    for ( ;; ) {
        fd = SFV_FD_SELF;
        prev = NULL;
        fprev = 0;
        file = NULL;
        sfv = NULL;
        eintr = 0;
        sent = 0;
        prev_send = send;

        nsfv = 0;

        /* create the sendfilevec and coalesce the neighbouring bufs */

        for (cl = in; cl && send < limit; cl = cl->next) {

            if (ngx_buf_special(cl->buf)) {
                continue;
            }

            if (ngx_buf_in_memory_only(cl->buf)) {
                fd = SFV_FD_SELF;

                size = cl->buf->last - cl->buf->pos;

                if (send + size > limit) {
                    size = limit - send;
                }

                if (prev == cl->buf->pos) {
                    sfv->sfv_len += (size_t) size;

                } else {
                    if (nsfv == NGX_SENDFILEVECS) {
                        break;
                    }

                    sfv = &sfvs[nsfv++];

                    sfv->sfv_fd = SFV_FD_SELF;
                    sfv->sfv_flag = 0;
                    sfv->sfv_off = (off_t) (uintptr_t) cl->buf->pos;
                    sfv->sfv_len = (size_t) size;
                }

                prev = cl->buf->pos + (size_t) size;
                send += size;

            } else {
                prev = NULL;

                size = cl->buf->file_last - cl->buf->file_pos;

                if (send + size > limit) {
                    size = limit - send;

                    aligned = (cl->buf->file_pos + size + ngx_pagesize - 1)
                               & ~((off_t) ngx_pagesize - 1);

                    if (aligned <= cl->buf->file_last) {
                        size = aligned - cl->buf->file_pos;
                    }
                }

                if (fd == cl->buf->file->fd && fprev == cl->buf->file_pos) {
                    sfv->sfv_len += (size_t) size;

                } else {
                    if (nsfv == NGX_SENDFILEVECS) {
                        break;
                    }

                    sfv = &sfvs[nsfv++];

                    fd = cl->buf->file->fd;
                    sfv->sfv_fd = fd;
                    sfv->sfv_flag = 0;
                    sfv->sfv_off = cl->buf->file_pos;
                    sfv->sfv_len = (size_t) size;
                }

                file = cl->buf;
                fprev = cl->buf->file_pos + size;
                send += size;
            }
        }

        n = sendfilev(c->fd, sfvs, nsfv, &sent);

        if (n == -1) {
            err = ngx_errno;

            switch (err) {
            case NGX_EAGAIN:
                break;

            case NGX_EINTR:
                eintr = 1;
                break;

            default:
                wev->error = 1;
                ngx_connection_error(c, err, "sendfilev() failed");
                return NGX_CHAIN_ERROR;
            }

            ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, err,
                          "sendfilev() sent only %uz bytes", sent);

        } else if (n == 0 && sent == 0) {

            /*
             * sendfilev() is documented to return -1 with errno
             * set to EINVAL if svf_len is greater than the file size,
             * but at least Solaris 11 returns 0 instead
             */

            if (file) {
                ngx_log_error(NGX_LOG_ALERT, c->log, 0,
                        "sendfilev() reported that \"%s\" was truncated at %O",
                        file->file->name.data, file->file_pos);

            } else {
                ngx_log_error(NGX_LOG_ALERT, c->log, 0,
                              "sendfilev() returned 0 with memory buffers");
            }

            return NGX_CHAIN_ERROR;
        }

        ngx_log_debug2(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "sendfilev: %z %z", n, sent);

        c->sent += sent;

        in = ngx_chain_update_sent(in, sent);

        if (eintr) {
            send = prev_send + sent;
            continue;
        }

        if (send - prev_send != (off_t) sent) {
            wev->ready = 0;
            return in;
        }

        if (send >= limit || in == NULL) {
            return in;
        }
    }
}