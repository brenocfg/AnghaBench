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
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 

__attribute__((used)) static int eafnosupport_ip6_del_rt(struct net *net, struct fib6_info *rt)
{
	return -EAFNOSUPPORT;
}