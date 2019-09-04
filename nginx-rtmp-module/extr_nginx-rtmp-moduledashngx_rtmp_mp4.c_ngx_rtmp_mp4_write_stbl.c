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
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_mp4_track_type_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_stco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_stsc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_stsd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_stsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_stts (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_stbl(ngx_rtmp_session_t *s, ngx_buf_t *b,
    ngx_rtmp_mp4_track_type_t ttype)
{
    u_char  *pos;

    pos = ngx_rtmp_mp4_start_box(b, "stbl");

    ngx_rtmp_mp4_write_stsd(s, b, ttype);
    ngx_rtmp_mp4_write_stts(b);
    ngx_rtmp_mp4_write_stsc(b);
    ngx_rtmp_mp4_write_stsz(b);
    ngx_rtmp_mp4_write_stco(b);

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}