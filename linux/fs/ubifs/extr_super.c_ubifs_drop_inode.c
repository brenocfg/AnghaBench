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
 int fscrypt_drop_inode (struct inode*) ; 
 int generic_drop_inode (struct inode*) ; 

__attribute__((used)) static int ubifs_drop_inode(struct inode *inode)
{
	int drop = generic_drop_inode(inode);

	if (!drop)
		drop = fscrypt_drop_inode(inode);

	return drop;
}