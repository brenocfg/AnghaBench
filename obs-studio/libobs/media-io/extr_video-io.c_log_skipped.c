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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 long os_atomic_load_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void log_skipped(video_t *video)
{
	long skipped = os_atomic_load_long(&video->skipped_frames);
	double percentage_skipped =
		(double)skipped /
		(double)os_atomic_load_long(&video->total_frames) * 100.0;

	if (skipped)
		blog(LOG_INFO,
		     "Video stopped, number of "
		     "skipped frames due "
		     "to encoding lag: "
		     "%ld/%ld (%0.1f%%)",
		     video->skipped_frames, video->total_frames,
		     percentage_skipped);
}