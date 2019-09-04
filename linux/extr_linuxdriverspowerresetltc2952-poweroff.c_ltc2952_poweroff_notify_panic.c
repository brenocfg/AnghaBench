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
struct ltc2952_poweroff {int kernel_panic; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  panic_notifier ; 
 struct ltc2952_poweroff* to_ltc2952 (struct notifier_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc2952_poweroff_notify_panic(struct notifier_block *nb,
					 unsigned long code, void *unused)
{
	struct ltc2952_poweroff *data = to_ltc2952(nb, panic_notifier);

	data->kernel_panic = true;
	return NOTIFY_DONE;
}