#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {size_t size; size_t data; size_t tail; scalar_t__ head; scalar_t__ sentinel; scalar_t__ count; } ;
typedef  TYPE_1__ ngx_http_lua_log_ringbuf_t ;

/* Variables and functions */
 size_t HEADER_LEN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_lua_log_ringbuf_append (TYPE_1__*,int,void*,size_t) ; 
 size_t ngx_http_lua_log_ringbuf_free_spaces (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_http_lua_log_ringbuf_throw_away (TYPE_1__*) ; 

ngx_int_t
ngx_http_lua_log_ringbuf_write(ngx_http_lua_log_ringbuf_t *rb, int log_level,
    void *buf, size_t n)
{
    if (n + HEADER_LEN > rb->size) {
        return NGX_ERROR;
    }

    if (ngx_http_lua_log_ringbuf_free_spaces(rb) < n + HEADER_LEN) {
        /* if the right space is not enough, mark it as placehold data */
        if ((size_t)(rb->data + rb->size - rb->tail) < n + HEADER_LEN) {

            while (rb->head >= rb->tail && rb->count) {
                /* head is after tail, so we will throw away all data between
                 * head and sentinel */
                ngx_http_lua_log_ringbuf_throw_away(rb);
            }

            rb->sentinel = rb->tail;
            rb->tail = rb->data;
        }

        while (ngx_http_lua_log_ringbuf_free_spaces(rb) < n + HEADER_LEN) {
            ngx_http_lua_log_ringbuf_throw_away(rb);
        }
    }

    ngx_http_lua_log_ringbuf_append(rb, log_level, buf, n);

    return NGX_OK;
}