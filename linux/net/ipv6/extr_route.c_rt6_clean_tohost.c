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
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_clean_all (struct net*,int /*<<< orphan*/ ,struct in6_addr*) ; 
 int /*<<< orphan*/  fib6_clean_tohost ; 

void rt6_clean_tohost(struct net *net, struct in6_addr *gateway)
{
	fib6_clean_all(net, fib6_clean_tohost, gateway);
}