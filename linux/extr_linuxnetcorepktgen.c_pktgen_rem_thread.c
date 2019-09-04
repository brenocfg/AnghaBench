#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pktgen_thread {TYPE_2__* net; TYPE_1__* tsk; } ;
struct TYPE_4__ {int /*<<< orphan*/  proc_dir; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pktgen_rem_thread(struct pktgen_thread *t)
{
	/* Remove from the thread list */
	remove_proc_entry(t->tsk->comm, t->net->proc_dir);
}