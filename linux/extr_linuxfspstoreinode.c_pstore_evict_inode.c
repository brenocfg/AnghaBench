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
struct pstore_private {int /*<<< orphan*/  list; } ;
struct inode {struct pstore_private* i_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  allpstore_lock ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  free_pstore_private (struct pstore_private*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pstore_evict_inode(struct inode *inode)
{
	struct pstore_private	*p = inode->i_private;
	unsigned long		flags;

	clear_inode(inode);
	if (p) {
		spin_lock_irqsave(&allpstore_lock, flags);
		list_del(&p->list);
		spin_unlock_irqrestore(&allpstore_lock, flags);
		free_pstore_private(p);
	}
}