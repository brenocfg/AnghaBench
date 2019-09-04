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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_3__ {scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_1__ ngx_rtmp_codec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_1__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_avcc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_video(ngx_rtmp_session_t *s, ngx_buf_t *b)
{
    u_char                *pos;
    ngx_rtmp_codec_ctx_t  *codec_ctx;

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    pos = ngx_rtmp_mp4_start_box(b, "avc1");

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_16(b, 0);

    /* data reference index */
    ngx_rtmp_mp4_field_16(b, 1);

    /* codec stream version & revision */
    ngx_rtmp_mp4_field_16(b, 0);
    ngx_rtmp_mp4_field_16(b, 0);

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);

    /* width & height */
    ngx_rtmp_mp4_field_16(b, (uint16_t) codec_ctx->width);
    ngx_rtmp_mp4_field_16(b, (uint16_t) codec_ctx->height);

    /* horizontal & vertical resolutions 72 dpi */
    ngx_rtmp_mp4_field_32(b, 0x00480000);
    ngx_rtmp_mp4_field_32(b, 0x00480000);

    /* data size */
    ngx_rtmp_mp4_field_32(b, 0);

    /* frame count */
    ngx_rtmp_mp4_field_16(b, 1);

    /* compressor name */
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_16(b, 0x18);
    ngx_rtmp_mp4_field_16(b, 0xffff);

    ngx_rtmp_mp4_write_avcc(s, b);

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}