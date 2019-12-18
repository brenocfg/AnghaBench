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
struct rtnexthop {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 struct rtnexthop* nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 struct rtnexthop* rtnh_next (struct rtnexthop*,int*) ; 
 scalar_t__ rtnh_ok (struct rtnexthop*,int) ; 

__attribute__((used)) static int dn_fib_count_nhs(const struct nlattr *attr)
{
	struct rtnexthop *nhp = nla_data(attr);
	int nhs = 0, nhlen = nla_len(attr);

	while (rtnh_ok(nhp, nhlen)) {
		nhs++;
		nhp = rtnh_next(nhp, &nhlen);
	}

	/* leftover implies invalid nexthop configuration, discard it */
	return nhlen > 0 ? 0 : nhs;
}