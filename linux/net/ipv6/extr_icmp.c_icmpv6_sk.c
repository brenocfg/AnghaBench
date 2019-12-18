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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * icmp_sk; } ;
struct net {TYPE_1__ ipv6; } ;

/* Variables and functions */
 struct sock* this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sock *icmpv6_sk(struct net *net)
{
	return this_cpu_read(*net->ipv6.icmp_sk);
}