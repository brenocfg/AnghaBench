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
struct ovl_inode {int /*<<< orphan*/  lock; int /*<<< orphan*/  redirect; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct ovl_inode* OVL_I (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ovl_inode*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_inode_cachep ; 

__attribute__((used)) static void ovl_free_inode(struct inode *inode)
{
	struct ovl_inode *oi = OVL_I(inode);

	kfree(oi->redirect);
	mutex_destroy(&oi->lock);
	kmem_cache_free(ovl_inode_cachep, oi);
}