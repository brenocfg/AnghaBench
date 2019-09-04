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
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *inet_fib_lookup_dev(struct net *net,
					      const void *addr)
{
	return ERR_PTR(-EAFNOSUPPORT);
}