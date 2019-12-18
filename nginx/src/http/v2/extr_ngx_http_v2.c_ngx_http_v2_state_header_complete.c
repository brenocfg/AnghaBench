#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_10__ {int /*<<< orphan*/  request; } ;
typedef  TYPE_2__ ngx_http_v2_stream_t ;
struct TYPE_9__ {int flags; scalar_t__ padding; scalar_t__ keep_pool; int /*<<< orphan*/ * pool; TYPE_2__* stream; int /*<<< orphan*/  handler; scalar_t__ length; } ;
struct TYPE_11__ {TYPE_1__ state; } ;
typedef  TYPE_3__ ngx_http_v2_connection_t ;

/* Variables and functions */
 int NGX_HTTP_V2_END_HEADERS_FLAG ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_handle_continuation (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  ngx_http_v2_run_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_complete (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_v2_state_header_block ; 
 int /*<<< orphan*/ * ngx_http_v2_state_skip_padded (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_header_complete(ngx_http_v2_connection_t *h2c, u_char *pos,
    u_char *end)
{
    ngx_http_v2_stream_t  *stream;

    if (h2c->state.length) {
        h2c->state.handler = ngx_http_v2_state_header_block;
        return pos;
    }

    if (!(h2c->state.flags & NGX_HTTP_V2_END_HEADERS_FLAG)) {
        return ngx_http_v2_handle_continuation(h2c, pos, end,
                                             ngx_http_v2_state_header_complete);
    }

    stream = h2c->state.stream;

    if (stream) {
        ngx_http_v2_run_request(stream->request);
    }

    if (!h2c->state.keep_pool) {
        ngx_destroy_pool(h2c->state.pool);
    }

    h2c->state.pool = NULL;
    h2c->state.keep_pool = 0;

    if (h2c->state.padding) {
        return ngx_http_v2_state_skip_padded(h2c, pos, end);
    }

    return ngx_http_v2_state_complete(h2c, pos, end);
}