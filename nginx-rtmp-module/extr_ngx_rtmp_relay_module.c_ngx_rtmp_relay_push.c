#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_10__ {int /*<<< orphan*/  url; } ;
struct TYPE_12__ {TYPE_2__ url; int /*<<< orphan*/  play_path; int /*<<< orphan*/  app; } ;
typedef  TYPE_4__ ngx_rtmp_relay_target_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_create (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_create_local_ctx ; 
 int /*<<< orphan*/  ngx_rtmp_relay_create_remote_ctx ; 

ngx_int_t
ngx_rtmp_relay_push(ngx_rtmp_session_t *s, ngx_str_t *name,
        ngx_rtmp_relay_target_t *target)
{
    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
            "relay: create push name='%V' app='%V' playpath='%V' url='%V'",
            name, &target->app, &target->play_path, &target->url.url);

    return ngx_rtmp_relay_create(s, name, target,
            ngx_rtmp_relay_create_local_ctx,
            ngx_rtmp_relay_create_remote_ctx);
}