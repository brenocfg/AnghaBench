#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct flowidn {int daddr; int saddr; } ;
struct TYPE_2__ {struct flowidn dn; } ;
struct flowi {TYPE_1__ u; } ;
struct fib_rule {int dummy; } ;
struct dn_fib_rule {int src; int srcmask; int dst; int dstmask; } ;
typedef  int __le16 ;

/* Variables and functions */

__attribute__((used)) static int dn_fib_rule_match(struct fib_rule *rule, struct flowi *fl, int flags)
{
	struct dn_fib_rule *r = (struct dn_fib_rule *)rule;
	struct flowidn *fld = &fl->u.dn;
	__le16 daddr = fld->daddr;
	__le16 saddr = fld->saddr;

	if (((saddr ^ r->src) & r->srcmask) ||
	    ((daddr ^ r->dst) & r->dstmask))
		return 0;

	return 1;
}