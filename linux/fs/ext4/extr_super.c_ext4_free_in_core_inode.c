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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  ext4_inode_cachep ; 
 int /*<<< orphan*/  fscrypt_free_inode (struct inode*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_free_in_core_inode(struct inode *inode)
{
	fscrypt_free_inode(inode);
	kmem_cache_free(ext4_inode_cachep, EXT4_I(inode));
}