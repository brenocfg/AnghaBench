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
struct kernel_lb_addr {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* __udf_iget (struct super_block*,struct kernel_lb_addr*,int) ; 

__attribute__((used)) static inline struct inode *udf_iget(struct super_block *sb,
				     struct kernel_lb_addr *ino)
{
	return __udf_iget(sb, ino, false);
}