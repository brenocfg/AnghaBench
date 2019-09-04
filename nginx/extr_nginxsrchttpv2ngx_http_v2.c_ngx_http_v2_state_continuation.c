#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_v2_connection_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/ * ngx_http_v2_connection_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_continuation(ngx_http_v2_connection_t *h2c, u_char *pos,
    u_char *end)
{
    ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                  "client sent unexpected CONTINUATION frame");

    return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_PROTOCOL_ERROR);
}