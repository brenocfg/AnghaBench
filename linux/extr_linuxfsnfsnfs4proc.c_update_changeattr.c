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
struct nfs4_change_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_changeattr_locked (struct inode*,struct nfs4_change_info*,unsigned long,unsigned long) ; 

__attribute__((used)) static void
update_changeattr(struct inode *dir, struct nfs4_change_info *cinfo,
		unsigned long timestamp, unsigned long cache_validity)
{
	spin_lock(&dir->i_lock);
	update_changeattr_locked(dir, cinfo, timestamp, cache_validity);
	spin_unlock(&dir->i_lock);
}