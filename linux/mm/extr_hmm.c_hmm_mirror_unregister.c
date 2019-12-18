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
struct hmm_mirror {int /*<<< orphan*/  list; struct hmm* hmm; } ;
struct hmm {int /*<<< orphan*/  mmu_notifier; int /*<<< orphan*/  mirrors_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_notifier_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void hmm_mirror_unregister(struct hmm_mirror *mirror)
{
	struct hmm *hmm = mirror->hmm;

	down_write(&hmm->mirrors_sem);
	list_del(&mirror->list);
	up_write(&hmm->mirrors_sem);
	mmu_notifier_put(&hmm->mmu_notifier);
}