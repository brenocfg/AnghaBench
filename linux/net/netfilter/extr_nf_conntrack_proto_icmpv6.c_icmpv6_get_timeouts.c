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
struct net {int dummy; } ;
struct TYPE_2__ {unsigned int timeout; } ;

/* Variables and functions */
 TYPE_1__* nf_icmpv6_pernet (struct net*) ; 

__attribute__((used)) static unsigned int *icmpv6_get_timeouts(struct net *net)
{
	return &nf_icmpv6_pernet(net)->timeout;
}