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
 int /*<<< orphan*/  ASSERT (int,char*) ; 
 int /*<<< orphan*/  FENCE_STATUS_ACTIVE ; 
 int /*<<< orphan*/  FENCE_STATUS_ERROR ; 
 int sync_fence_count_with_status (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int busy_wait_on_fence(int fence)
{
	int error, active;

	do {
		error = sync_fence_count_with_status(fence, FENCE_STATUS_ERROR);
		ASSERT(error == 0, "Error occurred on fence\n");
		active = sync_fence_count_with_status(fence,
						      FENCE_STATUS_ACTIVE);
	} while (active);

	return 0;
}