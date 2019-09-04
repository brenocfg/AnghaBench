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
struct pppox_sock {int dummy; } ;
struct pppoe_net {int /*<<< orphan*/  hash_lock; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct pppox_sock* __get_item (struct pppoe_net*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_pppox (struct pppox_sock*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct pppox_sock *get_item(struct pppoe_net *pn, __be16 sid,
					unsigned char *addr, int ifindex)
{
	struct pppox_sock *po;

	read_lock_bh(&pn->hash_lock);
	po = __get_item(pn, sid, addr, ifindex);
	if (po)
		sock_hold(sk_pppox(po));
	read_unlock_bh(&pn->hash_lock);

	return po;
}