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
struct tcf_proto {int /*<<< orphan*/  refcnt; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_proto_destroy (struct tcf_proto*,int,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static void tcf_proto_put(struct tcf_proto *tp, bool rtnl_held,
			  struct netlink_ext_ack *extack)
{
	if (refcount_dec_and_test(&tp->refcnt))
		tcf_proto_destroy(tp, rtnl_held, true, extack);
}