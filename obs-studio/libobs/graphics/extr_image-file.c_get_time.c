#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_6__ {TYPE_1__* frames; } ;
struct TYPE_7__ {TYPE_2__ gif; } ;
typedef  TYPE_3__ gs_image_file_t ;
struct TYPE_5__ {scalar_t__ frame_delay; } ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t get_time(gs_image_file_t *image, int i)
{
	uint64_t val = (uint64_t)image->gif.frames[i].frame_delay * 10000000ULL;
	if (!val)
		val = 100000000;
	return val;
}