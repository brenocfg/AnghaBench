#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_HANDSHAKE_DONE ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_cycle (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_2__*) ; 
 scalar_t__ ngx_rtmp_fire_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_free_handshake_buffers (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_rtmp_handshake_done(ngx_rtmp_session_t *s)
{
    ngx_rtmp_free_handshake_buffers(s);

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "handshake: done");

    if (ngx_rtmp_fire_event(s, NGX_RTMP_HANDSHAKE_DONE,
                NULL, NULL) != NGX_OK)
    {
        ngx_rtmp_finalize_session(s);
        return;
    }

    ngx_rtmp_cycle(s);
}