#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_fast32_t ;
struct v4l2_buffer_data {size_t count; TYPE_1__* info; } ;
typedef  int /*<<< orphan*/  int_fast32_t ;
struct TYPE_2__ {scalar_t__ start; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_munmap (scalar_t__,int /*<<< orphan*/ ) ; 

int_fast32_t v4l2_destroy_mmap(struct v4l2_buffer_data *buf)
{
	for (uint_fast32_t i = 0; i < buf->count; ++i) {
		if (buf->info[i].start != MAP_FAILED && buf->info[i].start != 0)
			v4l2_munmap(buf->info[i].start, buf->info[i].length);
	}

	if (buf->count) {
		bfree(buf->info);
		buf->count = 0;
	}

	return 0;
}