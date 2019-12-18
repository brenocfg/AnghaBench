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
struct integrity_iint_cache {int /*<<< orphan*/  rb_node; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_IMA (struct inode*) ; 
 struct integrity_iint_cache* __integrity_iint_find (struct inode*) ; 
 int /*<<< orphan*/  iint_free (struct integrity_iint_cache*) ; 
 int /*<<< orphan*/  integrity_iint_lock ; 
 int /*<<< orphan*/  integrity_iint_tree ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void integrity_inode_free(struct inode *inode)
{
	struct integrity_iint_cache *iint;

	if (!IS_IMA(inode))
		return;

	write_lock(&integrity_iint_lock);
	iint = __integrity_iint_find(inode);
	rb_erase(&iint->rb_node, &integrity_iint_tree);
	write_unlock(&integrity_iint_lock);

	iint_free(iint);
}