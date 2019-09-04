#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  next_close_stream ; 
 int /*<<< orphan*/  next_connect ; 
 int /*<<< orphan*/  next_disconnect ; 
 int /*<<< orphan*/  next_play ; 
 int /*<<< orphan*/  next_publish ; 
 int /*<<< orphan*/  next_record_done ; 
 int /*<<< orphan*/  ngx_rtmp_close_stream ; 
 int /*<<< orphan*/  ngx_rtmp_connect ; 
 int /*<<< orphan*/  ngx_rtmp_disconnect ; 
 int /*<<< orphan*/  ngx_rtmp_notify_close_stream ; 
 int /*<<< orphan*/  ngx_rtmp_notify_connect ; 
 int /*<<< orphan*/  ngx_rtmp_notify_disconnect ; 
 int /*<<< orphan*/  ngx_rtmp_notify_play ; 
 int /*<<< orphan*/  ngx_rtmp_notify_publish ; 
 int /*<<< orphan*/  ngx_rtmp_notify_record_done ; 
 int /*<<< orphan*/  ngx_rtmp_play ; 
 int /*<<< orphan*/  ngx_rtmp_publish ; 
 int /*<<< orphan*/  ngx_rtmp_record_done ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_notify_postconfiguration(ngx_conf_t *cf)
{
    next_connect = ngx_rtmp_connect;
    ngx_rtmp_connect = ngx_rtmp_notify_connect;

    next_disconnect = ngx_rtmp_disconnect;
    ngx_rtmp_disconnect = ngx_rtmp_notify_disconnect;

    next_publish = ngx_rtmp_publish;
    ngx_rtmp_publish = ngx_rtmp_notify_publish;

    next_play = ngx_rtmp_play;
    ngx_rtmp_play = ngx_rtmp_notify_play;

    next_close_stream = ngx_rtmp_close_stream;
    ngx_rtmp_close_stream = ngx_rtmp_notify_close_stream;

    next_record_done = ngx_rtmp_record_done;
    ngx_rtmp_record_done = ngx_rtmp_notify_record_done;

    return NGX_OK;
}