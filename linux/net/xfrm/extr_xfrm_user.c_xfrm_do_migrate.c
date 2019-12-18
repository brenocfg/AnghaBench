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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 

__attribute__((used)) static int xfrm_do_migrate(struct sk_buff *skb, struct nlmsghdr *nlh,
			   struct nlattr **attrs)
{
	return -ENOPROTOOPT;
}