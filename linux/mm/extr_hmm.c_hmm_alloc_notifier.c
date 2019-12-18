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
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;
struct hmm {struct mmu_notifier mmu_notifier; scalar_t__ notifiers; int /*<<< orphan*/  ranges_lock; int /*<<< orphan*/  ranges; int /*<<< orphan*/  mirrors_sem; int /*<<< orphan*/  mirrors; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mmu_notifier* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct hmm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mmu_notifier *hmm_alloc_notifier(struct mm_struct *mm)
{
	struct hmm *hmm;

	hmm = kzalloc(sizeof(*hmm), GFP_KERNEL);
	if (!hmm)
		return ERR_PTR(-ENOMEM);

	init_waitqueue_head(&hmm->wq);
	INIT_LIST_HEAD(&hmm->mirrors);
	init_rwsem(&hmm->mirrors_sem);
	INIT_LIST_HEAD(&hmm->ranges);
	spin_lock_init(&hmm->ranges_lock);
	hmm->notifiers = 0;
	return &hmm->mmu_notifier;
}