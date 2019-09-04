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
struct pppox_sock {int pppoe_ifindex; struct pppox_sock* next; int /*<<< orphan*/  pppoe_pa; } ;
struct pppoe_net {struct pppox_sock** hash_table; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ cmp_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int hash_item (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void __delete_item(struct pppoe_net *pn, __be16 sid,
					char *addr, int ifindex)
{
	int hash = hash_item(sid, addr);
	struct pppox_sock *ret, **src;

	ret = pn->hash_table[hash];
	src = &pn->hash_table[hash];

	while (ret) {
		if (cmp_addr(&ret->pppoe_pa, sid, addr) &&
		    ret->pppoe_ifindex == ifindex) {
			*src = ret->next;
			break;
		}

		src = &ret->next;
		ret = ret->next;
	}
}