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
 int /*<<< orphan*/  UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT ; 
 int ubifs_xattr_get (struct inode*,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int ubifs_crypt_get_context(struct inode *inode, void *ctx, size_t len)
{
	return ubifs_xattr_get(inode, UBIFS_XATTR_NAME_ENCRYPTION_CONTEXT,
			       ctx, len);
}