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

/* Variables and functions */
 struct inode* __isofs_iget (struct super_block*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct inode *isofs_iget(struct super_block *sb,
				       unsigned long block,
				       unsigned long offset)
{
	return __isofs_iget(sb, block, offset, 0);
}