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
struct sock {int dummy; } ;
struct hlist_head {int dummy; } ;
struct dn_scp {int /*<<< orphan*/  addrloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int EADDRINUSE ; 
 int EUSERS ; 
 struct hlist_head* dn_find_list (struct sock*) ; 
 int /*<<< orphan*/  dn_hash_lock ; 
 int /*<<< orphan*/  port_alloc (struct sock*) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,struct hlist_head*) ; 
 int /*<<< orphan*/  sk_hashed (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dn_hash_sock(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);
	struct hlist_head *list;
	int rv = -EUSERS;

	BUG_ON(sk_hashed(sk));

	write_lock_bh(&dn_hash_lock);

	if (!scp->addrloc && !port_alloc(sk))
		goto out;

	rv = -EADDRINUSE;
	if ((list = dn_find_list(sk)) == NULL)
		goto out;

	sk_add_node(sk, list);
	rv = 0;
out:
	write_unlock_bh(&dn_hash_lock);
	return rv;
}