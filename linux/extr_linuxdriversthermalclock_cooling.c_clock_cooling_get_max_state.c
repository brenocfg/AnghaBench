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
struct thermal_cooling_device {struct clock_cooling_device* devdata; } ;
struct clock_cooling_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MAXL ; 
 int clock_cooling_get_property (struct clock_cooling_device*,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clock_cooling_get_max_state(struct thermal_cooling_device *cdev,
				       unsigned long *state)
{
	struct clock_cooling_device *ccdev = cdev->devdata;
	unsigned long count = 0;
	int ret;

	ret = clock_cooling_get_property(ccdev, 0, &count, GET_MAXL);
	if (!ret)
		*state = count;

	return ret;
}