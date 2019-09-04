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
struct notifier_block {int dummy; } ;
struct clock_cooling_device {int /*<<< orphan*/  clock_val; } ;
struct clk_notifier_data {int /*<<< orphan*/  new_rate; } ;

/* Variables and functions */
#define  ABORT_RATE_CHANGE 130 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
#define  POST_RATE_CHANGE 129 
#define  PRE_RATE_CHANGE 128 
 struct clock_cooling_device* to_clock_cooling_device (struct notifier_block*) ; 

__attribute__((used)) static int clock_cooling_clock_notifier(struct notifier_block *nb,
					unsigned long event, void *data)
{
	struct clk_notifier_data *ndata = data;
	struct clock_cooling_device *ccdev = to_clock_cooling_device(nb);

	switch (event) {
	case PRE_RATE_CHANGE:
		/*
		 * checks on current state
		 * TODO: current method is not best we can find as it
		 * allows possibly voltage transitions, in case DVFS
		 * layer is also hijacking clock pre notifications.
		 */
		if (ndata->new_rate > ccdev->clock_val)
			return NOTIFY_BAD;
		/* fall through */
	case POST_RATE_CHANGE:
	case ABORT_RATE_CHANGE:
	default:
		return NOTIFY_DONE;
	}
}