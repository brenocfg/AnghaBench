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
 int /*<<< orphan*/  next_play ; 
 int /*<<< orphan*/  next_publish ; 
 int /*<<< orphan*/  ngx_rtmp_access_play ; 
 int /*<<< orphan*/  ngx_rtmp_access_publish ; 
 int /*<<< orphan*/  ngx_rtmp_play ; 
 int /*<<< orphan*/  ngx_rtmp_publish ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_access_postconfiguration(ngx_conf_t *cf)
{
    /* chain handlers */
    next_publish = ngx_rtmp_publish;
    ngx_rtmp_publish = ngx_rtmp_access_publish;

    next_play = ngx_rtmp_play;
    ngx_rtmp_play = ngx_rtmp_access_play;

    return NGX_OK;
}