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
struct nfs4_ff_layout_mirror {TYPE_1__* layout; int /*<<< orphan*/  mirrors; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {struct inode* plh_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ff_layout_remove_mirror(struct nfs4_ff_layout_mirror *mirror)
{
	struct inode *inode;
	if (mirror->layout == NULL)
		return;
	inode = mirror->layout->plh_inode;
	spin_lock(&inode->i_lock);
	list_del(&mirror->mirrors);
	spin_unlock(&inode->i_lock);
	mirror->layout = NULL;
}