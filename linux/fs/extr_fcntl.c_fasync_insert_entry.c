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
struct file {int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_flags; } ;
struct fasync_struct {int fa_fd; struct fasync_struct* fa_next; struct file* fa_file; int /*<<< orphan*/  magic; int /*<<< orphan*/  fa_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FASYNC ; 
 int /*<<< orphan*/  FASYNC_MAGIC ; 
 int /*<<< orphan*/  fasync_lock ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct fasync_struct*,struct fasync_struct*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

struct fasync_struct *fasync_insert_entry(int fd, struct file *filp, struct fasync_struct **fapp, struct fasync_struct *new)
{
        struct fasync_struct *fa, **fp;

	spin_lock(&filp->f_lock);
	spin_lock(&fasync_lock);
	for (fp = fapp; (fa = *fp) != NULL; fp = &fa->fa_next) {
		if (fa->fa_file != filp)
			continue;

		write_lock_irq(&fa->fa_lock);
		fa->fa_fd = fd;
		write_unlock_irq(&fa->fa_lock);
		goto out;
	}

	rwlock_init(&new->fa_lock);
	new->magic = FASYNC_MAGIC;
	new->fa_file = filp;
	new->fa_fd = fd;
	new->fa_next = *fapp;
	rcu_assign_pointer(*fapp, new);
	filp->f_flags |= FASYNC;

out:
	spin_unlock(&fasync_lock);
	spin_unlock(&filp->f_lock);
	return fa;
}