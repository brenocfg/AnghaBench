#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {scalar_t__ status; } ;
struct TYPE_11__ {TYPE_3__* out; TYPE_1__ headers_out; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_9__ {TYPE_2__* buf; } ;
struct TYPE_8__ {scalar_t__ pos; scalar_t__ last; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssi_set_variable(ngx_http_request_t *r, void *data, ngx_int_t rc)
{
    ngx_str_t  *value = data;

    if (r->headers_out.status < NGX_HTTP_SPECIAL_RESPONSE
        && r->out && r->out->buf)
    {
        value->len = r->out->buf->last - r->out->buf->pos;
        value->data = r->out->buf->pos;
    }

    return rc;
}