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
struct TYPE_9__ {int /*<<< orphan*/  phase_handler; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_stream_session_t ;
struct TYPE_10__ {scalar_t__ (* handler ) (TYPE_2__*) ;int /*<<< orphan*/  next; } ;
typedef  TYPE_3__ ngx_stream_phase_handler_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_STREAM_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_finalize_session (TYPE_2__*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

ngx_int_t
ngx_stream_core_generic_phase(ngx_stream_session_t *s,
    ngx_stream_phase_handler_t *ph)
{
    ngx_int_t  rc;

    /*
     * generic phase checker,
     * used by all phases, except for preread and content
     */

    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                   "generic phase: %ui", s->phase_handler);

    rc = ph->handler(s);

    if (rc == NGX_OK) {
        s->phase_handler = ph->next;
        return NGX_AGAIN;
    }

    if (rc == NGX_DECLINED) {
        s->phase_handler++;
        return NGX_AGAIN;
    }

    if (rc == NGX_AGAIN || rc == NGX_DONE) {
        return NGX_OK;
    }

    if (rc == NGX_ERROR) {
        rc = NGX_STREAM_INTERNAL_SERVER_ERROR;
    }

    ngx_stream_finalize_session(s, rc);

    return NGX_OK;
}