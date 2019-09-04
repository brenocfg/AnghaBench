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
struct ct_timer_instance {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct_systimer_callback ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ct_systimer_init(struct ct_timer_instance *ti)
{
	timer_setup(&ti->timer, ct_systimer_callback, 0);
}