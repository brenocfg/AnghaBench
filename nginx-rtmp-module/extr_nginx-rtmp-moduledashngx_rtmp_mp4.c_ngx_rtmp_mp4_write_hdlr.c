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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_rtmp_mp4_track_type_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ NGX_RTMP_MP4_VIDEO_TRACK ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_data (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_hdlr(ngx_buf_t *b, ngx_rtmp_mp4_track_type_t ttype)
{
    u_char  *pos;

    pos = ngx_rtmp_mp4_start_box(b, "hdlr");

    /* version and flags */
    ngx_rtmp_mp4_field_32(b, 0);

    /* pre defined */
    ngx_rtmp_mp4_field_32(b, 0);

    if (ttype == NGX_RTMP_MP4_VIDEO_TRACK) {
        ngx_rtmp_mp4_box(b, "vide");
    } else {
        ngx_rtmp_mp4_box(b, "soun");
    }

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);

    if (ttype == NGX_RTMP_MP4_VIDEO_TRACK) {
        /* video handler string, NULL-terminated */
        ngx_rtmp_mp4_data(b, "VideoHandler", sizeof("VideoHandler"));
    } else {
        /* sound handler string, NULL-terminated */
        ngx_rtmp_mp4_data(b, "SoundHandler", sizeof("SoundHandler"));
    }

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}