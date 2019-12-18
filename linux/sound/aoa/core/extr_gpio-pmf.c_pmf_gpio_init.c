#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct gpio_runtime {TYPE_1__ line_out_notify; TYPE_3__ line_in_notify; TYPE_2__ headphone_notify; scalar_t__ implementation_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_gpio_all_amps_off (struct gpio_runtime*) ; 
 int /*<<< orphan*/  pmf_handle_notify ; 

__attribute__((used)) static void pmf_gpio_init(struct gpio_runtime *rt)
{
	pmf_gpio_all_amps_off(rt);
	rt->implementation_private = 0;
	INIT_DELAYED_WORK(&rt->headphone_notify.work, pmf_handle_notify);
	INIT_DELAYED_WORK(&rt->line_in_notify.work, pmf_handle_notify);
	INIT_DELAYED_WORK(&rt->line_out_notify.work, pmf_handle_notify);
	mutex_init(&rt->headphone_notify.mutex);
	mutex_init(&rt->line_in_notify.mutex);
	mutex_init(&rt->line_out_notify.mutex);
}