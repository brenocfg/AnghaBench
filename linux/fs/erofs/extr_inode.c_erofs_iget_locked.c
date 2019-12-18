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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  erofs_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  erofs_iget_set_actor ; 
 int /*<<< orphan*/  erofs_ilookup_test_actor ; 
 unsigned long erofs_inode_hash (int /*<<< orphan*/ ) ; 
 struct inode* iget5_locked (struct super_block*,unsigned long const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct inode *erofs_iget_locked(struct super_block *sb,
					      erofs_nid_t nid)
{
	const unsigned long hashval = erofs_inode_hash(nid);

	return iget5_locked(sb, hashval, erofs_ilookup_test_actor,
		erofs_iget_set_actor, &nid);
}