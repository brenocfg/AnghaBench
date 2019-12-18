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
typedef  size_t uint8_t ;
struct in6_addr {scalar_t__* s6_addr; } ;
struct TYPE_2__ {struct in6_addr v6; } ;
struct cidr {scalar_t__ family; TYPE_1__ addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 struct cidr* cidr_clone (struct cidr*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool cidr_sub6(struct cidr *a, struct cidr *b)
{
	uint8_t idx = 15, carry = 0, underflow = 0;

	struct cidr *n = cidr_clone(a);
	struct in6_addr *x = &n->addr.v6;
	struct in6_addr *y = &b->addr.v6;

	if ((n->family != AF_INET6) || (b->family != AF_INET6))
		return false;

	do {
		underflow = !!((x->s6_addr[idx] - y->s6_addr[idx] - carry) < 0);
		x->s6_addr[idx] -= y->s6_addr[idx] + carry;
		carry = underflow;
	}
	while (idx-- > 0);

	if (carry)
	{
		fprintf(stderr, "underflow during 'sub'\n");
		return false;
	}

	return true;
}