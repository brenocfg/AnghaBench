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
struct TYPE_2__ {int /*<<< orphan*/  fib_num_tclassid_users; } ;
struct net {TYPE_1__ ipv4; } ;
struct fib_nh {int /*<<< orphan*/  nh_common; scalar_t__ nh_tclassid; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib_nh_common_release (int /*<<< orphan*/ *) ; 

void fib_nh_release(struct net *net, struct fib_nh *fib_nh)
{
#ifdef CONFIG_IP_ROUTE_CLASSID
	if (fib_nh->nh_tclassid)
		net->ipv4.fib_num_tclassid_users--;
#endif
	fib_nh_common_release(&fib_nh->nh_common);
}