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
struct inet_diag_req_v2 {int dummy; } ;

/* Variables and functions */
 int udp_dump_one (int /*<<< orphan*/ *,struct sk_buff*,struct nlmsghdr const*,struct inet_diag_req_v2 const*) ; 
 int /*<<< orphan*/  udp_table ; 

__attribute__((used)) static int udp_diag_dump_one(struct sk_buff *in_skb, const struct nlmsghdr *nlh,
			     const struct inet_diag_req_v2 *req)
{
	return udp_dump_one(&udp_table, in_skb, nlh, req);
}