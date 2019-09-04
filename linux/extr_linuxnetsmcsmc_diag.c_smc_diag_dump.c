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
struct netlink_callback {int dummy; } ;

/* Variables and functions */
 int smc_diag_dump_proto (int /*<<< orphan*/ *,struct sk_buff*,struct netlink_callback*) ; 
 int /*<<< orphan*/  smc_proto ; 
 int /*<<< orphan*/  smc_proto6 ; 

__attribute__((used)) static int smc_diag_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	int rc = 0;

	rc = smc_diag_dump_proto(&smc_proto, skb, cb);
	if (!rc)
		rc = smc_diag_dump_proto(&smc_proto6, skb, cb);
	return rc;
}