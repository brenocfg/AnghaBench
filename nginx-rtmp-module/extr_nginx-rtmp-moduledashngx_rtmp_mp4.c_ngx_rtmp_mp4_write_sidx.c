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
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_rtmp_mp4_write_sidx(ngx_buf_t *b, ngx_uint_t reference_size,
    uint32_t earliest_pres_time, uint32_t latest_pres_time)
{
    u_char    *pos;
    uint32_t   duration;

    duration = latest_pres_time - earliest_pres_time;

    pos = ngx_rtmp_mp4_start_box(b, "sidx");

    /* version */
    ngx_rtmp_mp4_field_32(b, 0);

    /* reference id */
    ngx_rtmp_mp4_field_32(b, 1);

    /* timescale */
    ngx_rtmp_mp4_field_32(b, 1000);

    /* earliest presentation time */
    ngx_rtmp_mp4_field_32(b, earliest_pres_time);

    /* first offset */
    ngx_rtmp_mp4_field_32(b, duration); /*TODO*/

    /* reserved */
    ngx_rtmp_mp4_field_16(b, 0);

    /* reference count = 1 */
    ngx_rtmp_mp4_field_16(b, 1);

    /* 1st bit is reference type, the rest is reference size */
    ngx_rtmp_mp4_field_32(b, reference_size);

    /* subsegment duration */
    ngx_rtmp_mp4_field_32(b, duration);

    /* first bit is startsWithSAP (=1), next 3 bits are SAP type (=001) */
    ngx_rtmp_mp4_field_8(b, 0x90);

    /* SAP delta time */
    ngx_rtmp_mp4_field_24(b, 0);

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}