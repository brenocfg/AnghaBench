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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_matrix(ngx_buf_t *buf, uint32_t a, uint32_t b, uint32_t c,
    uint32_t d, uint32_t tx, uint32_t ty)
{

/*
 * transformation matrix
 * |a  b  u|
 * |c  d  v|
 * |tx ty w|
 */

    ngx_rtmp_mp4_field_32(buf, a << 16);  /* 16.16 format */
    ngx_rtmp_mp4_field_32(buf, b << 16);  /* 16.16 format */
    ngx_rtmp_mp4_field_32(buf, 0);        /* u in 2.30 format */
    ngx_rtmp_mp4_field_32(buf, c << 16);  /* 16.16 format */
    ngx_rtmp_mp4_field_32(buf, d << 16);  /* 16.16 format */
    ngx_rtmp_mp4_field_32(buf, 0);        /* v in 2.30 format */
    ngx_rtmp_mp4_field_32(buf, tx << 16); /* 16.16 format */
    ngx_rtmp_mp4_field_32(buf, ty << 16); /* 16.16 format */
    ngx_rtmp_mp4_field_32(buf, 1 << 30);  /* w in 2.30 format */

    return NGX_OK;
}