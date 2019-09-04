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
typedef  int /*<<< orphan*/  u32 ;
struct netlink_compare_arg {int /*<<< orphan*/  portid; int /*<<< orphan*/  pnet; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct netlink_compare_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 

__attribute__((used)) static void netlink_compare_arg_init(struct netlink_compare_arg *arg,
				     struct net *net, u32 portid)
{
	memset(arg, 0, sizeof(*arg));
	write_pnet(&arg->pnet, net);
	arg->portid = portid;
}