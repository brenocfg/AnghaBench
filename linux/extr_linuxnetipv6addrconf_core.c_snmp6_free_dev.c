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
struct TYPE_2__ {int /*<<< orphan*/  ipv6; int /*<<< orphan*/  icmpv6dev; int /*<<< orphan*/  icmpv6msgdev; } ;
struct inet6_dev {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snmp6_free_dev(struct inet6_dev *idev)
{
	kfree(idev->stats.icmpv6msgdev);
	kfree(idev->stats.icmpv6dev);
	free_percpu(idev->stats.ipv6);
}