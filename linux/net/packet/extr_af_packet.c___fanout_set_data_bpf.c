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
struct packet_fanout {int /*<<< orphan*/  lock; int /*<<< orphan*/  bpf_prog; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_destroy (struct bpf_prog*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 struct bpf_prog* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

__attribute__((used)) static void __fanout_set_data_bpf(struct packet_fanout *f, struct bpf_prog *new)
{
	struct bpf_prog *old;

	spin_lock(&f->lock);
	old = rcu_dereference_protected(f->bpf_prog, lockdep_is_held(&f->lock));
	rcu_assign_pointer(f->bpf_prog, new);
	spin_unlock(&f->lock);

	if (old) {
		synchronize_net();
		bpf_prog_destroy(old);
	}
}