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
 unsigned int ALIGN_DOWN (unsigned int,int) ; 
 unsigned int CUR_ADDRS_PER_INODE (struct inode*) ; 
 unsigned int get_inline_xattr_addrs (struct inode*) ; 

__attribute__((used)) static inline unsigned int addrs_per_inode(struct inode *inode)
{
	unsigned int addrs = CUR_ADDRS_PER_INODE(inode) -
				get_inline_xattr_addrs(inode);
	return ALIGN_DOWN(addrs, 1);
}