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
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_lock (struct super_block*) ; 
 TYPE_1__* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  hpfs_unlock (struct super_block*) ; 
 int /*<<< orphan*/  lazy_free_sbi ; 
 int /*<<< orphan*/  unmark_dirty (struct super_block*) ; 

__attribute__((used)) static void hpfs_put_super(struct super_block *s)
{
	hpfs_lock(s);
	unmark_dirty(s);
	hpfs_unlock(s);
	call_rcu(&hpfs_sb(s)->rcu, lazy_free_sbi);
}