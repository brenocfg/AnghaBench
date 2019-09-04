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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_matrix (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_mvhd(ngx_buf_t *b)
{
    u_char  *pos;

    pos = ngx_rtmp_mp4_start_box(b, "mvhd");

    /* version */
    ngx_rtmp_mp4_field_32(b, 0);

    /* creation time */
    ngx_rtmp_mp4_field_32(b, 0);

    /* modification time */
    ngx_rtmp_mp4_field_32(b, 0);

    /* timescale */
    ngx_rtmp_mp4_field_32(b, 1000);

    /* duration */
    ngx_rtmp_mp4_field_32(b, 0);

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0x00010000);
    ngx_rtmp_mp4_field_16(b, 0x0100);
    ngx_rtmp_mp4_field_16(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);

    ngx_rtmp_mp4_write_matrix(b, 1, 0, 0, 1, 0, 0);

    /* reserved */
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);
    ngx_rtmp_mp4_field_32(b, 0);

    /* next track id */
    ngx_rtmp_mp4_field_32(b, 1);

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}