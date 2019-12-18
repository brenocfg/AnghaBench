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
struct TYPE_3__ {int /*<<< orphan*/  skipped_frames; } ;
typedef  TYPE_1__ video_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_atomic_load_long (int /*<<< orphan*/ *) ; 

uint32_t video_output_get_skipped_frames(const video_t *video)
{
	return (uint32_t)os_atomic_load_long(&video->skipped_frames);
}