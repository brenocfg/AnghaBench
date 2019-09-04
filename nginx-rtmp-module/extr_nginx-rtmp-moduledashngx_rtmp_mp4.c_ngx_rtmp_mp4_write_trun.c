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
typedef  int ngx_uint_t ;
struct TYPE_3__ {int duration; int size; int delay; scalar_t__ key; } ;
typedef  TYPE_1__ ngx_rtmp_mp4_sample_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_RTMP_MP4_SAMPLE_DELAY ; 
 int NGX_RTMP_MP4_SAMPLE_DURATION ; 
 int NGX_RTMP_MP4_SAMPLE_KEY ; 
 int NGX_RTMP_MP4_SAMPLE_SIZE ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_field_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_trun(ngx_buf_t *b, uint32_t sample_count,
    ngx_rtmp_mp4_sample_t *samples, ngx_uint_t sample_mask, u_char *moof_pos)
{
    u_char    *pos;
    uint32_t   i, offset, nitems, flags;

    pos = ngx_rtmp_mp4_start_box(b, "trun");

    nitems = 0;

    /* data offset present */
    flags = 0x01;

    if (sample_mask & NGX_RTMP_MP4_SAMPLE_DURATION) {
        nitems++;
        flags |= 0x000100;
    }

    if (sample_mask & NGX_RTMP_MP4_SAMPLE_SIZE) {
        nitems++;
        flags |= 0x000200;
    }

    if (sample_mask & NGX_RTMP_MP4_SAMPLE_KEY) {
        nitems++;
        flags |= 0x000400;
    }

    if (sample_mask & NGX_RTMP_MP4_SAMPLE_DELAY) {
        nitems++;
        flags |= 0x000800;
    }

    offset = (pos - moof_pos) + 20 + (sample_count * nitems * 4) + 8;

    ngx_rtmp_mp4_field_32(b, flags);
    ngx_rtmp_mp4_field_32(b, sample_count);
    ngx_rtmp_mp4_field_32(b, offset);

    for (i = 0; i < sample_count; i++, samples++) {

        if (sample_mask & NGX_RTMP_MP4_SAMPLE_DURATION) {
            ngx_rtmp_mp4_field_32(b, samples->duration);
        }

        if (sample_mask & NGX_RTMP_MP4_SAMPLE_SIZE) {
            ngx_rtmp_mp4_field_32(b, samples->size);
        }

        if (sample_mask & NGX_RTMP_MP4_SAMPLE_KEY) {
            ngx_rtmp_mp4_field_32(b, samples->key ? 0x00000000 : 0x00010000);
        }

        if (sample_mask & NGX_RTMP_MP4_SAMPLE_DELAY) {
            ngx_rtmp_mp4_field_32(b, samples->delay);
        }
    }

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}