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
typedef  size_t uint32_t ;
struct obs_source_frame {size_t* linesize; size_t* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,size_t,size_t) ; 

__attribute__((used)) static inline void copy_frame_data_line(struct obs_source_frame *dst,
					const struct obs_source_frame *src,
					uint32_t plane, uint32_t y)
{
	uint32_t pos_src = y * src->linesize[plane];
	uint32_t pos_dst = y * dst->linesize[plane];
	uint32_t bytes = dst->linesize[plane] < src->linesize[plane]
				 ? dst->linesize[plane]
				 : src->linesize[plane];

	memcpy(dst->data[plane] + pos_dst, src->data[plane] + pos_src, bytes);
}