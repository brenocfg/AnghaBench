#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ a4; TYPE_1__ a6; } ;
struct qeth_ipaddr {scalar_t__ proto; TYPE_3__ u; } ;

/* Variables and functions */
 scalar_t__ QETH_PROT_IPV6 ; 
 int ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool qeth_l3_addr_match_ip(struct qeth_ipaddr *a1,
					 struct qeth_ipaddr *a2)
{
	if (a1->proto != a2->proto)
		return false;
	if (a1->proto == QETH_PROT_IPV6)
		return ipv6_addr_equal(&a1->u.a6.addr, &a2->u.a6.addr);
	return a1->u.a4.addr == a2->u.a4.addr;
}