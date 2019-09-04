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
struct padata_instance {int flags; int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int PADATA_INIT ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  padata_flush_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void __padata_stop(struct padata_instance *pinst)
{
	if (!(pinst->flags & PADATA_INIT))
		return;

	pinst->flags &= ~PADATA_INIT;

	synchronize_rcu();

	get_online_cpus();
	padata_flush_queues(pinst->pd);
	put_online_cpus();
}