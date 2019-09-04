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
struct packet_sock {struct packet_fanout* fanout; } ;
struct packet_fanout {int num_members; int /*<<< orphan*/  lock; int /*<<< orphan*/  prot_hook; struct sock** arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __dev_remove_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __fanout_unlink(struct sock *sk, struct packet_sock *po)
{
	struct packet_fanout *f = po->fanout;
	int i;

	spin_lock(&f->lock);
	for (i = 0; i < f->num_members; i++) {
		if (f->arr[i] == sk)
			break;
	}
	BUG_ON(i >= f->num_members);
	f->arr[i] = f->arr[f->num_members - 1];
	f->num_members--;
	if (f->num_members == 0)
		__dev_remove_pack(&f->prot_hook);
	spin_unlock(&f->lock);
}