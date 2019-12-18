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
struct nlattr {int dummy; } ;
struct netlink_callback {int dummy; } ;
struct inet_diag_req_v2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udp_dump (int /*<<< orphan*/ *,struct sk_buff*,struct netlink_callback*,struct inet_diag_req_v2 const*,struct nlattr*) ; 
 int /*<<< orphan*/  udplite_table ; 

__attribute__((used)) static void udplite_diag_dump(struct sk_buff *skb, struct netlink_callback *cb,
			      const struct inet_diag_req_v2 *r,
			      struct nlattr *bc)
{
	udp_dump(&udplite_table, skb, cb, r, bc);
}