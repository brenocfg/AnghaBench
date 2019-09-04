#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aa_profile {TYPE_1__** dents; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mtime; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_3__* d_inode; } ;

/* Variables and functions */
 int AAFS_PROF_SIZEOF ; 
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  current_time (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 TYPE_2__* profiles_ns (struct aa_profile*) ; 

void __aafs_profile_migrate_dents(struct aa_profile *old,
				  struct aa_profile *new)
{
	int i;

	AA_BUG(!old);
	AA_BUG(!new);
	AA_BUG(!mutex_is_locked(&profiles_ns(old)->lock));

	for (i = 0; i < AAFS_PROF_SIZEOF; i++) {
		new->dents[i] = old->dents[i];
		if (new->dents[i])
			new->dents[i]->d_inode->i_mtime = current_time(new->dents[i]->d_inode);
		old->dents[i] = NULL;
	}
}