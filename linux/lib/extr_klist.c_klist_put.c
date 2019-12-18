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
struct klist_node {int dummy; } ;
struct klist {void (* put ) (struct klist_node*) ;int /*<<< orphan*/  k_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  klist_dec_and_del (struct klist_node*) ; 
 int /*<<< orphan*/  knode_kill (struct klist_node*) ; 
 struct klist* knode_klist (struct klist_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void klist_put(struct klist_node *n, bool kill)
{
	struct klist *k = knode_klist(n);
	void (*put)(struct klist_node *) = k->put;

	spin_lock(&k->k_lock);
	if (kill)
		knode_kill(n);
	if (!klist_dec_and_del(n))
		put = NULL;
	spin_unlock(&k->k_lock);
	if (put)
		put(n);
}