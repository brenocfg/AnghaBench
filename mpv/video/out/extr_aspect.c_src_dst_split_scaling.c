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

/* Variables and functions */
 int /*<<< orphan*/  clamp_size (int,int*,int*) ; 
 int powf (int,float) ; 

__attribute__((used)) static void src_dst_split_scaling(int src_size, int dst_size,
                                  int scaled_src_size,
                                  float zoom, float align, float pan,
                                  int *src_start, int *src_end,
                                  int *dst_start, int *dst_end,
                                  int *osd_margin_a, int *osd_margin_b)
{
    scaled_src_size *= powf(2, zoom);
    align = (align + 1) / 2;

    *src_start = 0;
    *src_end = src_size;
    *dst_start = (dst_size - scaled_src_size) * align + pan * scaled_src_size;
    *dst_end = *dst_start + scaled_src_size;

    // Clip to screen
    int s_src = *src_end - *src_start;
    int s_dst = *dst_end - *dst_start;
    if (*dst_start < 0) {
        int border = -(*dst_start) * s_src / s_dst;
        *src_start += border;
        *dst_start = 0;
    }
    if (*dst_end > dst_size) {
        int border = (*dst_end - dst_size) * s_src / s_dst;
        *src_end -= border;
        *dst_end = dst_size;
    }

    // For sanity: avoid bothering VOs with corner cases
    clamp_size(src_size, src_start, src_end);
    clamp_size(dst_size, dst_start, dst_end);

    // Distance of screen frame to video
    *osd_margin_a = *dst_start;
    *osd_margin_b = dst_size - *dst_end;
}