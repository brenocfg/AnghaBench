#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * rl; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * rl; } ;
struct TYPE_7__ {scalar_t__ name; scalar_t__ name_len; TYPE_2__ attr_list_rl; int /*<<< orphan*/ * attr_list; TYPE_1__ runlist; } ;
typedef  TYPE_3__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ I30 ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  ntfs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ntfs_clear_inode(ntfs_inode *ni)
{
	/* Free all alocated memory. */
	down_write(&ni->runlist.lock);
	if (ni->runlist.rl) {
		ntfs_free(ni->runlist.rl);
		ni->runlist.rl = NULL;
	}
	up_write(&ni->runlist.lock);

	if (ni->attr_list) {
		ntfs_free(ni->attr_list);
		ni->attr_list = NULL;
	}

	down_write(&ni->attr_list_rl.lock);
	if (ni->attr_list_rl.rl) {
		ntfs_free(ni->attr_list_rl.rl);
		ni->attr_list_rl.rl = NULL;
	}
	up_write(&ni->attr_list_rl.lock);

	if (ni->name_len && ni->name != I30) {
		/* Catch bugs... */
		BUG_ON(!ni->name);
		kfree(ni->name);
	}
}