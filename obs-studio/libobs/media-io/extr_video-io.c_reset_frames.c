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
struct TYPE_3__ {int /*<<< orphan*/  total_frames; int /*<<< orphan*/  skipped_frames; } ;
typedef  TYPE_1__ video_t ;

/* Variables and functions */
 int /*<<< orphan*/  os_atomic_set_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reset_frames(video_t *video)
{
	os_atomic_set_long(&video->skipped_frames, 0);
	os_atomic_set_long(&video->total_frames, 0);
}