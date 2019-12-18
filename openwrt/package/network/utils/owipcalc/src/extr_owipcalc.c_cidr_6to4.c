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
typedef  int uint32_t ;
struct TYPE_5__ {int* s6_addr; } ;
struct TYPE_4__ {int s_addr; } ;
struct TYPE_6__ {TYPE_2__ v6; TYPE_1__ v4; } ;
struct cidr {int prefix; TYPE_3__ addr; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 struct cidr* cidr_clone (struct cidr*) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool cidr_6to4(struct cidr *a)
{
	struct cidr *n = cidr_clone(a);
	uint32_t x = a->addr.v4.s_addr;

	memset(&n->addr.v6.s6_addr, 0, sizeof(n->addr.v6.s6_addr));

	n->family = AF_INET6;
	n->prefix = 48;

	n->addr.v6.s6_addr[0] = 0x20;
	n->addr.v6.s6_addr[1] = 0x02;
	n->addr.v6.s6_addr[2] = (x >> 24);
	n->addr.v6.s6_addr[3] = (x >> 16) & 0xFF;
	n->addr.v6.s6_addr[4] = (x >>  8) & 0xFF;
	n->addr.v6.s6_addr[5] = x & 0xFF;

	return true;
}