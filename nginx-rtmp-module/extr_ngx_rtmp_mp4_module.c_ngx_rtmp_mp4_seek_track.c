#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_12__ {int valid; } ;
struct TYPE_11__ {TYPE_2__ cursor; } ;
typedef  TYPE_1__ ngx_rtmp_mp4_track_t ;
typedef  TYPE_2__ ngx_rtmp_mp4_cursor_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_from_rtmp_timestamp (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ngx_rtmp_mp4_seek_chunk (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ngx_rtmp_mp4_seek_delay (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ngx_rtmp_mp4_seek_key (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ngx_rtmp_mp4_seek_size (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ngx_rtmp_mp4_seek_time (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_seek_track(ngx_rtmp_session_t *s, ngx_rtmp_mp4_track_t *t,
                        ngx_int_t timestamp)
{
    ngx_rtmp_mp4_cursor_t          *cr;

    cr = &t->cursor;
    ngx_memzero(cr, sizeof(*cr));

    if (ngx_rtmp_mp4_seek_time(s, t, ngx_rtmp_mp4_from_rtmp_timestamp(
                          t, timestamp)) != NGX_OK ||
        ngx_rtmp_mp4_seek_key(s, t)   != NGX_OK ||
        ngx_rtmp_mp4_seek_chunk(s, t) != NGX_OK ||
        ngx_rtmp_mp4_seek_size(s, t)  != NGX_OK ||
        ngx_rtmp_mp4_seek_delay(s, t) != NGX_OK)
    {
        return NGX_ERROR;
    }

    cr->valid = 1;
    return NGX_OK;
}