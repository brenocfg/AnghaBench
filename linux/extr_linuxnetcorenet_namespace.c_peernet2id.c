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
struct net {int /*<<< orphan*/  nsid_lock; } ;

/* Variables and functions */
 int __peernet2id (struct net*,struct net*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int peernet2id(struct net *net, struct net *peer)
{
	int id;

	spin_lock_bh(&net->nsid_lock);
	id = __peernet2id(net, peer);
	spin_unlock_bh(&net->nsid_lock);
	return id;
}