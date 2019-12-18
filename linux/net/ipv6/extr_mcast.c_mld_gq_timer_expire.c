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
struct inet6_dev {scalar_t__ mc_gq_running; } ;

/* Variables and functions */
 struct inet6_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* idev ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  mc_gq_timer ; 
 int /*<<< orphan*/  mld_send_report (struct inet6_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mld_gq_timer_expire(struct timer_list *t)
{
	struct inet6_dev *idev = from_timer(idev, t, mc_gq_timer);

	idev->mc_gq_running = 0;
	mld_send_report(idev, NULL);
	in6_dev_put(idev);
}