#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_1__* first; } ;
typedef  TYPE_2__ ngx_http_v2_out_frame_t ;
struct TYPE_9__ {TYPE_2__* free_frames; } ;
typedef  TYPE_3__ ngx_http_v2_connection_t ;
struct TYPE_10__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_7__ {TYPE_4__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_frame_handler(ngx_http_v2_connection_t *h2c,
    ngx_http_v2_out_frame_t *frame)
{
    ngx_buf_t  *buf;

    buf = frame->first->buf;

    if (buf->pos != buf->last) {
        return NGX_AGAIN;
    }

    frame->next = h2c->free_frames;
    h2c->free_frames = frame;

    return NGX_OK;
}