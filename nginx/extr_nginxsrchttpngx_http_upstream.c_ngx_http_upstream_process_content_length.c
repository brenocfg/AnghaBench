#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_2__ value; } ;
typedef  TYPE_3__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  content_length_n; TYPE_3__* content_length; } ;
struct TYPE_11__ {TYPE_1__ headers_in; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_12__ {TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_atoof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_content_length(ngx_http_request_t *r,
    ngx_table_elt_t *h, ngx_uint_t offset)
{
    ngx_http_upstream_t  *u;

    u = r->upstream;

    u->headers_in.content_length = h;
    u->headers_in.content_length_n = ngx_atoof(h->value.data, h->value.len);

    return NGX_OK;
}