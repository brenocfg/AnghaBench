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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_mp4_sample_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_mfhd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_write_traf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_rtmp_mp4_write_moof(ngx_buf_t *b, uint32_t earliest_pres_time,
    uint32_t sample_count, ngx_rtmp_mp4_sample_t *samples,
    ngx_uint_t sample_mask, uint32_t index)
{
    u_char  *pos;

    pos = ngx_rtmp_mp4_start_box(b, "moof");

    ngx_rtmp_mp4_write_mfhd(b, index);
    ngx_rtmp_mp4_write_traf(b, earliest_pres_time, sample_count, samples,
                            sample_mask, pos);

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}