#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_12__ {TYPE_1__ value; } ;
typedef  TYPE_4__ ngx_http_v2_header_t ;
struct TYPE_13__ {TYPE_2__* stream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_10__ {int /*<<< orphan*/ * cookies; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ngx_array_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_cookie(ngx_http_request_t *r, ngx_http_v2_header_t *header)
{
    ngx_str_t    *val;
    ngx_array_t  *cookies;

    cookies = r->stream->cookies;

    if (cookies == NULL) {
        cookies = ngx_array_create(r->pool, 2, sizeof(ngx_str_t));
        if (cookies == NULL) {
            return NGX_ERROR;
        }

        r->stream->cookies = cookies;
    }

    val = ngx_array_push(cookies);
    if (val == NULL) {
        return NGX_ERROR;
    }

    val->len = header->value.len;
    val->data = header->value.data;

    return NGX_OK;
}