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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 TYPE_1__* HUGETLBFS_I (struct inode*) ; 
 int /*<<< orphan*/  HUGETLBFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlbfs_inc_free_inodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_free_shared_policy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hugetlbfs_destroy_inode(struct inode *inode)
{
	hugetlbfs_inc_free_inodes(HUGETLBFS_SB(inode->i_sb));
	mpol_free_shared_policy(&HUGETLBFS_I(inode)->policy);
}