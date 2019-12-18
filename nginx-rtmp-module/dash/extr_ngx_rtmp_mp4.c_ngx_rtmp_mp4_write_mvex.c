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
 int /*<<< orphan*/  ngx_rtmp_mp4_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_mvex(ngx_buf_t *b)
{
    u_char  *pos;

    pos = ngx_rtmp_mp4_start_box(b, "mvex");

    ngx_rtmp_mp4_field_32(b, 0x20);

    ngx_rtmp_mp4_box(b, "trex");

    /* version & flags */
    ngx_rtmp_mp4_field_32(b, 0);

    /* track id */
    ngx_rtmp_mp4_field_32(b, 1);

    /* default sample description index */
    ngx_rtmp_mp4_field_32(b, 1);

    /* default sample duration */
    ngx_rtmp_mp4_field_32(b, 0);

    /* default sample size, 1024 for AAC */
    ngx_rtmp_mp4_field_32(b, 0);

    /* default sample flags, key on */
    ngx_rtmp_mp4_field_32(b, 0);

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}