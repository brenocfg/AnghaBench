#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_5__ {int /*<<< orphan*/  body_start; TYPE_1__* buf; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ ngx_http_cache_t ;
struct TYPE_4__ {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_read_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

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