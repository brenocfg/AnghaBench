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
struct bpf_prog {TYPE_1__* aux; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  __acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  prog_idr ; 
 int /*<<< orphan*/  prog_idr_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void bpf_prog_free_id(struct bpf_prog *prog, bool do_idr_lock)
{
	/* cBPF to eBPF migrations are currently not in the idr store.
	 * Offloaded programs are removed from the store when their device
	 * disappears - even if someone grabs an fd to them they are unusable,
	 * simply waiting for refcnt to drop to be freed.
	 */
	if (!prog->aux->id)
		return;

	if (do_idr_lock)
		spin_lock_bh(&prog_idr_lock);
	else
		__acquire(&prog_idr_lock);

	idr_remove(&prog_idr, prog->aux->id);
	prog->aux->id = 0;

	if (do_idr_lock)
		spin_unlock_bh(&prog_idr_lock);
	else
		__release(&prog_idr_lock);
}