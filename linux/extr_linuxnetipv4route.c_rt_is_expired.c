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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct rtable {scalar_t__ rt_genid; TYPE_1__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ rt_genid_ipv4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool rt_is_expired(const struct rtable *rth)
{
	return rth->rt_genid != rt_genid_ipv4(dev_net(rth->dst.dev));
}