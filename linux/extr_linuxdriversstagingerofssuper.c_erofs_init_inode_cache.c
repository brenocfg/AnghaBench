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
struct erofs_vnode {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/ * erofs_inode_cachep ; 
 int /*<<< orphan*/  init_once ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int erofs_init_inode_cache(void)
{
	erofs_inode_cachep = kmem_cache_create("erofs_inode",
		sizeof(struct erofs_vnode), 0,
		SLAB_RECLAIM_ACCOUNT, init_once);

	return erofs_inode_cachep != NULL ? 0 : -ENOMEM;
}