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
struct file_lock {int /*<<< orphan*/  fl_flags; } ;
struct plock_xop {int (* callback ) (struct file_lock*,int) ;struct file_lock* fl; struct file_lock flc; struct file* file; } ;
struct TYPE_2__ {int rv; scalar_t__ number; } ;
struct plock_op {TYPE_1__ info; int /*<<< orphan*/  list; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_SLEEP ; 
 int /*<<< orphan*/  kfree (struct plock_xop*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_print (char*,...) ; 
 int /*<<< orphan*/  ops_lock ; 
 scalar_t__ posix_lock_file (struct file*,struct file_lock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_plock_callback(struct plock_op *op)
{
	struct file *file;
	struct file_lock *fl;
	struct file_lock *flc;
	int (*notify)(struct file_lock *fl, int result) = NULL;
	struct plock_xop *xop = (struct plock_xop *)op;
	int rv = 0;

	spin_lock(&ops_lock);
	if (!list_empty(&op->list)) {
		log_print("dlm_plock_callback: op on list %llx",
			  (unsigned long long)op->info.number);
		list_del(&op->list);
	}
	spin_unlock(&ops_lock);

	/* check if the following 2 are still valid or make a copy */
	file = xop->file;
	flc = &xop->flc;
	fl = xop->fl;
	notify = xop->callback;

	if (op->info.rv) {
		notify(fl, op->info.rv);
		goto out;
	}

	/* got fs lock; bookkeep locally as well: */
	flc->fl_flags &= ~FL_SLEEP;
	if (posix_lock_file(file, flc, NULL)) {
		/*
		 * This can only happen in the case of kmalloc() failure.
		 * The filesystem's own lock is the authoritative lock,
		 * so a failure to get the lock locally is not a disaster.
		 * As long as the fs cannot reliably cancel locks (especially
		 * in a low-memory situation), we're better off ignoring
		 * this failure than trying to recover.
		 */
		log_print("dlm_plock_callback: vfs lock error %llx file %p fl %p",
			  (unsigned long long)op->info.number, file, fl);
	}

	rv = notify(fl, 0);
	if (rv) {
		/* XXX: We need to cancel the fs lock here: */
		log_print("dlm_plock_callback: lock granted after lock request "
			  "failed; dangling lock!\n");
		goto out;
	}

out:
	kfree(xop);
	return rv;
}