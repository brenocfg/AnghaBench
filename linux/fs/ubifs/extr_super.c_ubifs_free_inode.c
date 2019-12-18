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
struct ubifs_inode {int /*<<< orphan*/  data; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fscrypt_free_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ubifs_inode*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int /*<<< orphan*/  ubifs_inode_slab ; 

__attribute__((used)) static void ubifs_free_inode(struct inode *inode)
{
	struct ubifs_inode *ui = ubifs_inode(inode);

	kfree(ui->data);
	fscrypt_free_inode(inode);

	kmem_cache_free(ubifs_inode_slab, ui);
}