#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_17__ {int aio; int /*<<< orphan*/  pool; TYPE_2__* main; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_18__ {scalar_t__ aio; } ;
typedef  TYPE_5__ ngx_http_core_loc_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  thread_task; TYPE_4__* thread_ctx; int /*<<< orphan*/  thread_handler; TYPE_1__* aio; } ;
struct TYPE_19__ {int reading; int /*<<< orphan*/  body_start; TYPE_3__* buf; TYPE_7__ file; int /*<<< orphan*/  thread_task; } ;
typedef  TYPE_6__ ngx_http_cache_t ;
struct TYPE_16__ {int /*<<< orphan*/  pos; } ;
struct TYPE_15__ {int /*<<< orphan*/  blocked; } ;
struct TYPE_14__ {int /*<<< orphan*/  handler; TYPE_4__* data; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_HTTP_AIO_ON ; 
 scalar_t__ NGX_HTTP_AIO_THREADS ; 
 scalar_t__ ngx_file_aio ; 
 scalar_t__ ngx_file_aio_read (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_cache_aio_event_handler ; 
 int /*<<< orphan*/  ngx_http_cache_thread_handler ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_read_file (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_thread_read (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ngx_http_file_cache_aio_read(ngx_http_request_t *r, ngx_http_cache_t *c)
{
#if (NGX_HAVE_FILE_AIO || NGX_THREADS)
    ssize_t                    n;
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
#endif

#if (NGX_HAVE_FILE_AIO)

    if (clcf->aio == NGX_HTTP_AIO_ON && ngx_file_aio) {
        n = ngx_file_aio_read(&c->file, c->buf->pos, c->body_start, 0, r->pool);

        if (n != NGX_AGAIN) {
            c->reading = 0;
            return n;
        }

        c->reading = 1;

        c->file.aio->data = r;
        c->file.aio->handler = ngx_http_cache_aio_event_handler;

        r->main->blocked++;
        r->aio = 1;

        return NGX_AGAIN;
    }

#endif

#if (NGX_THREADS)

    if (clcf->aio == NGX_HTTP_AIO_THREADS) {
        c->file.thread_task = c->thread_task;
        c->file.thread_handler = ngx_http_cache_thread_handler;
        c->file.thread_ctx = r;

        n = ngx_thread_read(&c->file, c->buf->pos, c->body_start, 0, r->pool);

        c->thread_task = c->file.thread_task;
        c->reading = (n == NGX_AGAIN);

        return n;
    }

#endif

    return ngx_read_file(&c->file, c->buf->pos, c->body_start, 0);
}