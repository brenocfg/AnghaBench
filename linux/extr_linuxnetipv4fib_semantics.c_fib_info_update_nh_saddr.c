#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev_addr_genid; } ;
struct net {TYPE_2__ ipv4; } ;
struct fib_nh {int /*<<< orphan*/  nh_saddr; int /*<<< orphan*/  nh_saddr_genid; TYPE_1__* nh_parent; int /*<<< orphan*/  nh_gw; int /*<<< orphan*/  nh_dev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  fib_scope; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_select_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__be32 fib_info_update_nh_saddr(struct net *net, struct fib_nh *nh)
{
	nh->nh_saddr = inet_select_addr(nh->nh_dev,
					nh->nh_gw,
					nh->nh_parent->fib_scope);
	nh->nh_saddr_genid = atomic_read(&net->ipv4.dev_addr_genid);

	return nh->nh_saddr;
}