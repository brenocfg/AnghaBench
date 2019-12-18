#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_RTMP_MSG_CHUNK_SIZE ; 
 int /*<<< orphan*/  NGX_RTMP_USER_END (TYPE_2__*) ; 
 int /*<<< orphan*/  NGX_RTMP_USER_OUT4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGX_RTMP_USER_START (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

ngx_chain_t *
ngx_rtmp_create_abort(ngx_rtmp_session_t *s, uint32_t csid)
{
    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "create: abort csid=%uD", csid);

    {
        NGX_RTMP_USER_START(s, NGX_RTMP_MSG_CHUNK_SIZE);

        NGX_RTMP_USER_OUT4(csid);

        NGX_RTMP_USER_END(s);
    }
}