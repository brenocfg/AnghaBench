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
struct at86rf230_local {int sleep; TYPE_1__* data; int /*<<< orphan*/  slp_tr; } ;
struct TYPE_2__ {scalar_t__ t_sleep_to_off; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
at86rf230_awake(struct at86rf230_local *lp)
{
	if (gpio_is_valid(lp->slp_tr)) {
		gpio_set_value(lp->slp_tr, 0);
		usleep_range(lp->data->t_sleep_to_off,
			     lp->data->t_sleep_to_off + 100);
		lp->sleep = false;
	}
}