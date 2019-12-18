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
 int /*<<< orphan*/  next_pause ; 
 int /*<<< orphan*/  next_play ; 
 int /*<<< orphan*/  next_seek ; 
 int /*<<< orphan*/  ngx_rtmp_close_stream ; 
 int /*<<< orphan*/  ngx_rtmp_pause ; 
 int /*<<< orphan*/  ngx_rtmp_play ; 
 int /*<<< orphan*/  ngx_rtmp_play_close_stream ; 
 int /*<<< orphan*/  ngx_rtmp_play_pause ; 
 int /*<<< orphan*/  ngx_rtmp_play_play ; 
 int /*<<< orphan*/  ngx_rtmp_play_seek ; 
 int /*<<< orphan*/  ngx_rtmp_seek ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_postconfiguration(ngx_conf_t *cf)
{
    next_play = ngx_rtmp_play;
    ngx_rtmp_play = ngx_rtmp_play_play;

    next_close_stream = ngx_rtmp_close_stream;
    ngx_rtmp_close_stream = ngx_rtmp_play_close_stream;

    next_seek = ngx_rtmp_seek;
    ngx_rtmp_seek = ngx_rtmp_play_seek;

    next_pause = ngx_rtmp_pause;
    ngx_rtmp_pause = ngx_rtmp_play_pause;

    return NGX_OK;
}