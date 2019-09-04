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
struct xattr_handler {int dummy; } ;

/* Variables and functions */
 int SQUASHFS_XATTR_PREFIX_MASK ; 
#define  SQUASHFS_XATTR_SECURITY 130 
#define  SQUASHFS_XATTR_TRUSTED 129 
#define  SQUASHFS_XATTR_USER 128 
 int SQUASHFS_XATTR_VALUE_OOL ; 
 struct xattr_handler const squashfs_xattr_security_handler ; 
 struct xattr_handler const squashfs_xattr_trusted_handler ; 
 struct xattr_handler const squashfs_xattr_user_handler ; 

__attribute__((used)) static const struct xattr_handler *squashfs_xattr_handler(int type)
{
	if (type & ~(SQUASHFS_XATTR_PREFIX_MASK | SQUASHFS_XATTR_VALUE_OOL))
		/* ignore unrecognised type */
		return NULL;

	switch (type & SQUASHFS_XATTR_PREFIX_MASK) {
	case SQUASHFS_XATTR_USER:
		return &squashfs_xattr_user_handler;
	case SQUASHFS_XATTR_TRUSTED:
		return &squashfs_xattr_trusted_handler;
	case SQUASHFS_XATTR_SECURITY:
		return &squashfs_xattr_security_handler;
	default:
		/* ignore unrecognised type */
		return NULL;
	}
}