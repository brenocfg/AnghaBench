#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_5__ {TYPE_4__* connection; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ ngx_stream_session_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_close_connection (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_stream_log_session (TYPE_1__*) ; 

void
ngx_stream_finalize_session(ngx_stream_session_t *s, ngx_uint_t rc)
{
    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                   "finalize stream session: %i", rc);

    s->status = rc;

    ngx_stream_log_session(s);

    ngx_stream_close_connection(s->connection);
}