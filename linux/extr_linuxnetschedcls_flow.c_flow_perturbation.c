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
struct timer_list {int dummy; } ;
struct flow_filter {scalar_t__ perturb_period; int /*<<< orphan*/  perturb_timer; int /*<<< orphan*/  hashrnd; } ;

/* Variables and functions */
 struct flow_filter* f ; 
 struct flow_filter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  perturb_timer ; 

__attribute__((used)) static void flow_perturbation(struct timer_list *t)
{
	struct flow_filter *f = from_timer(f, t, perturb_timer);

	get_random_bytes(&f->hashrnd, 4);
	if (f->perturb_period)
		mod_timer(&f->perturb_timer, jiffies + f->perturb_period);
}