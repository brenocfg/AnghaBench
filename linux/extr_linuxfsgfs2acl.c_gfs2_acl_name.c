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

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 char const* XATTR_POSIX_ACL_ACCESS ; 
 char const* XATTR_POSIX_ACL_DEFAULT ; 

__attribute__((used)) static const char *gfs2_acl_name(int type)
{
	switch (type) {
	case ACL_TYPE_ACCESS:
		return XATTR_POSIX_ACL_ACCESS;
	case ACL_TYPE_DEFAULT:
		return XATTR_POSIX_ACL_DEFAULT;
	}
	return NULL;
}