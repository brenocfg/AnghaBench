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
typedef  struct dsp_image_seg const dsp_image_seg ;
typedef  scalar_t__ p ;

/* Variables and functions */
 scalar_t__ dsp_sizeof (struct dsp_image_seg const*) ; 

__attribute__((used)) static const struct dsp_image_seg *get_next_seg_ptr(
				const struct dsp_image_seg *p)
{
	return (struct dsp_image_seg *)((unsigned char *)(p) + dsp_sizeof(p));
}