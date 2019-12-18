#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  scalar_t__ ngx_rtmp_mp4_track_type_t ;
struct TYPE_3__ {scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_1__ ngx_rtmp_codec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ NGX_RTMP_MP4_VIDEO_TRACK ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_1__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_matrix (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_tkhd(ngx_rtmp_session_t *s, ngx_buf_t *b,
    ngx_rtmp_mp4_track_type_t ttype)
{
    u_char                *pos;
    ngx_rtmp_codec_ctx_t  *codec_ctx;

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    pos = ngx_rtmp_mp4_start_box(b, "tkhd");

    /* version */
    ngx_rtmp_mp4_field_8(b, 0);

    /* flags: TrackEnabled */
    ngx_rtmp_mp4_field_24(b, 0x0000000f);

    /* creation time */
    ngx_rtmp_mp4_field_32(b, 0);

    /* modification time */
    ngx_rtmp_mp4_field_32(b, 0);

    /* track id */
    ngx_rtmp_mp4_field_32(b, 1);

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0);

    /* duration */
    ngx_rtmp_mp4_field_32(b, 0);

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);

    /* reserved */
    ngx_rtmp_mp4_field_16(b, ttype == NGX_RTMP_MP4_VIDEO_TRACK ?  0 : 0x0100);

    /* reserved */
    ngx_rtmp_mp4_field_16(b, 0);

    ngx_rtmp_mp4_write_matrix(b, 1, 0, 0, 1, 0, 0);

    if (ttype == NGX_RTMP_MP4_VIDEO_TRACK) {
        ngx_rtmp_mp4_field_32(b, (uint32_t) codec_ctx->width << 16);
        ngx_rtmp_mp4_field_32(b, (uint32_t) codec_ctx->height << 16);
    } else {
        ngx_rtmp_mp4_field_32(b, 0);
        ngx_rtmp_mp4_field_32(b, 0);
    }

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}