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
struct packet_fanout {size_t num_members; int /*<<< orphan*/  lock; int /*<<< orphan*/  prot_hook; struct sock** arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_add_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __fanout_link(struct sock *sk, struct packet_sock *po)
{
	struct packet_fanout *f = po->fanout;

	spin_lock(&f->lock);
	f->arr[f->num_members] = sk;
	smp_wmb();
	f->num_members++;
	if (f->num_members == 1)
		dev_add_pack(&f->prot_hook);
	spin_unlock(&f->lock);
}