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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct niu {TYPE_1__ timer; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct niu* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int niu_link_status (struct niu*,int*) ; 
 int /*<<< orphan*/  niu_link_status_common (struct niu*,int) ; 
 struct niu* np ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void niu_timer(struct timer_list *t)
{
	struct niu *np = from_timer(np, t, timer);
	unsigned long off;
	int err, link_up;

	err = niu_link_status(np, &link_up);
	if (!err)
		niu_link_status_common(np, link_up);

	if (netif_carrier_ok(np->dev))
		off = 5 * HZ;
	else
		off = 1 * HZ;
	np->timer.expires = jiffies + off;

	add_timer(&np->timer);
}