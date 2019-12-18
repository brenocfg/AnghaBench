#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  last_modified_time; } ;
struct TYPE_10__ {TYPE_4__* if_unmodified_since; } ;
struct TYPE_13__ {TYPE_2__ headers_out; TYPE_1__* connection; TYPE_3__ headers_in; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_5__ value; } ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_parse_http_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_uint_t
ngx_http_test_if_unmodified(ngx_http_request_t *r)
{
    time_t  iums;

    if (r->headers_out.last_modified_time == (time_t) -1) {
        return 0;
    }

    iums = ngx_parse_http_time(r->headers_in.if_unmodified_since->value.data,
                               r->headers_in.if_unmodified_since->value.len);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                 "http iums:%T lm:%T", iums, r->headers_out.last_modified_time);

    if (iums >= r->headers_out.last_modified_time) {
        return 1;
    }

    return 0;
}