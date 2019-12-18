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
struct file {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ fscrypt_get_encryption_info (struct inode*) ; 

__attribute__((used)) static int ext4_dir_open(struct inode * inode, struct file * filp)
{
	if (IS_ENCRYPTED(inode))
		return fscrypt_get_encryption_info(inode) ? -EACCES : 0;
	return 0;
}