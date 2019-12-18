#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_http_v2_handler_pt ;
struct TYPE_6__ {size_t buffer_used; int incomplete; int /*<<< orphan*/  handler; int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {TYPE_1__ state; TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_http_v2_connection_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_INTERNAL_ERROR ; 
 size_t NGX_HTTP_V2_STATE_BUFFER_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/ * ngx_http_v2_connection_error (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_save(ngx_http_v2_connection_t *h2c, u_char *pos, u_char *end,
    ngx_http_v2_handler_pt handler)
{
    size_t  size;

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2 frame state save pos:%p end:%p handler:%p",
                   pos, end, handler);

    size = end - pos;

    if (size > NGX_HTTP_V2_STATE_BUFFER_SIZE) {
        ngx_log_error(NGX_LOG_ALERT, h2c->connection->log, 0,
                      "state buffer overflow: %uz bytes required", size);

        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_INTERNAL_ERROR);
    }

    ngx_memcpy(h2c->state.buffer, pos, NGX_HTTP_V2_STATE_BUFFER_SIZE);

    h2c->state.buffer_used = size;
    h2c->state.handler = handler;
    h2c->state.incomplete = 1;

    return end;
}