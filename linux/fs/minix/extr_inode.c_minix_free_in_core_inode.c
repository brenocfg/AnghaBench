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
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minix_i (struct inode*) ; 
 int /*<<< orphan*/  minix_inode_cachep ; 

__attribute__((used)) static void minix_free_in_core_inode(struct inode *inode)
{
	kmem_cache_free(minix_inode_cachep, minix_i(inode));
}