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
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_play_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_ACCESS_PLAY ; 
 int /*<<< orphan*/  next_play (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_rtmp_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_access_play(ngx_rtmp_session_t *s, ngx_rtmp_play_t *v)
{
    if (ngx_rtmp_access(s, NGX_RTMP_ACCESS_PLAY) != NGX_OK) {
        return NGX_ERROR;
    }

    return next_play(s, v);
}