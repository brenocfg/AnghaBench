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
 int EPERM ; 
 int /*<<< orphan*/  fscrypt_has_permitted_context (struct inode*,struct inode*) ; 
 int fscrypt_require_key (struct inode*) ; 

int __fscrypt_prepare_link(struct inode *inode, struct inode *dir)
{
	int err;

	err = fscrypt_require_key(dir);
	if (err)
		return err;

	if (!fscrypt_has_permitted_context(dir, inode))
		return -EPERM;

	return 0;
}