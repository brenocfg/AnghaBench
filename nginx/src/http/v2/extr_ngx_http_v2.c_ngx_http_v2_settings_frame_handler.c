#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {TYPE_6__* first; } ;
typedef  TYPE_1__ ngx_http_v2_out_frame_t ;
struct TYPE_8__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_v2_connection_t ;
struct TYPE_9__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_3__ ngx_buf_t ;
struct TYPE_10__ {TYPE_3__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_free_chain (int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_settings_frame_handler(ngx_http_v2_connection_t *h2c,
    ngx_http_v2_out_frame_t *frame)
{
    ngx_buf_t  *buf;

    buf = frame->first->buf;

    if (buf->pos != buf->last) {
        return NGX_AGAIN;
    }

    ngx_free_chain(h2c->pool, frame->first);

    return NGX_OK;
}