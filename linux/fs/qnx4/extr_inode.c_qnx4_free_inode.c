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
 int /*<<< orphan*/  qnx4_i (struct inode*) ; 
 int /*<<< orphan*/  qnx4_inode_cachep ; 

__attribute__((used)) static void qnx4_free_inode(struct inode *inode)
{
	kmem_cache_free(qnx4_inode_cachep, qnx4_i(inode));
}