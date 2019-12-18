#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {int last_modified_time; } ;
struct TYPE_10__ {TYPE_1__ headers_out; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_header_val_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_set_response_header (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int ngx_parse_http_time (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_http_set_last_modified(ngx_http_request_t *r, ngx_http_header_val_t *hv,
    ngx_str_t *value)
{
    if (ngx_http_set_response_header(r, hv, value) != NGX_OK) {
        return NGX_ERROR;
    }

    r->headers_out.last_modified_time =
        (value->len) ? ngx_parse_http_time(value->data, value->len) : -1;

    return NGX_OK;
}