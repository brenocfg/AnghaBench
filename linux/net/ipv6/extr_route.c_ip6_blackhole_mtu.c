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
struct dst_entry {TYPE_1__* dev; } ;
struct TYPE_2__ {unsigned int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAX_MTU ; 
 unsigned int dst_metric_raw (struct dst_entry const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ip6_blackhole_mtu(const struct dst_entry *dst)
{
	unsigned int mtu = dst_metric_raw(dst, RTAX_MTU);

	return mtu ? : dst->dev->mtu;
}