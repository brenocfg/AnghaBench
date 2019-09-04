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
struct knav_range_info {int dummy; } ;
struct knav_device {int dummy; } ;

/* Variables and functions */
 struct knav_range_info* first_queue_range (struct knav_device*) ; 
 int /*<<< orphan*/  knav_free_queue_range (struct knav_device*,struct knav_range_info*) ; 

__attribute__((used)) static void knav_free_queue_ranges(struct knav_device *kdev)
{
	struct knav_range_info *range;

	for (;;) {
		range = first_queue_range(kdev);
		if (!range)
			break;
		knav_free_queue_range(kdev, range);
	}
}