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
typedef  int uint8_t ;
struct in6_addr {int* s6_addr; } ;
struct TYPE_2__ {struct in6_addr v6; } ;
struct cidr {int prefix; TYPE_1__ addr; } ;

/* Variables and functions */
 struct cidr* cidr_clone (struct cidr*) ; 
 int /*<<< orphan*/  memcmp (int**,int**,int) ; 
 scalar_t__ printed ; 
 int /*<<< orphan*/  qprintf (char*) ; 

__attribute__((used)) static bool cidr_contains6(struct cidr *a, struct cidr *b)
{
	struct cidr *n = cidr_clone(a);
	struct in6_addr *x = &n->addr.v6;
	struct in6_addr *y = &b->addr.v6;
	uint8_t i = (128 - n->prefix) / 8;
	uint8_t m = ~((1 << ((128 - n->prefix) % 8)) - 1);
	uint8_t net1 = x->s6_addr[15-i] & m;
	uint8_t net2 = y->s6_addr[15-i] & m;

	if (printed)
		qprintf(" ");

	if ((b->prefix >= n->prefix) && (net1 == net2) &&
	    ((i == 15) || !memcmp(&x->s6_addr, &y->s6_addr, 15-i)))
	{
		qprintf("1");
		return true;
	}
	else
	{
		qprintf("0");
		return false;
	}
}