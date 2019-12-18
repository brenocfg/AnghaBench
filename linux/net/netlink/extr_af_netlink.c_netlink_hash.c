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
struct netlink_sock {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;
struct netlink_compare_arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_compare_arg_init (struct netlink_compare_arg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int netlink_compare_arg_len ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 netlink_hash(const void *data, u32 len, u32 seed)
{
	const struct netlink_sock *nlk = data;
	struct netlink_compare_arg arg;

	netlink_compare_arg_init(&arg, sock_net(&nlk->sk), nlk->portid);
	return jhash2((u32 *)&arg, netlink_compare_arg_len / sizeof(u32), seed);
}