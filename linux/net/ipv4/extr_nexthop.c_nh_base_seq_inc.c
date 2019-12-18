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
struct TYPE_2__ {scalar_t__ seq; } ;
struct net {TYPE_1__ nexthop; } ;

/* Variables and functions */

__attribute__((used)) static void nh_base_seq_inc(struct net *net)
{
	while (++net->nexthop.seq == 0)
		;
}