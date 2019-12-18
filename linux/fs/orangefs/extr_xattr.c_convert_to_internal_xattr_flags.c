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
 int ORANGEFS_XATTR_CREATE ; 
 int ORANGEFS_XATTR_REPLACE ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 

__attribute__((used)) static inline int convert_to_internal_xattr_flags(int setxattr_flags)
{
	int internal_flag = 0;

	if (setxattr_flags & XATTR_REPLACE) {
		/* Attribute must exist! */
		internal_flag = ORANGEFS_XATTR_REPLACE;
	} else if (setxattr_flags & XATTR_CREATE) {
		/* Attribute must not exist */
		internal_flag = ORANGEFS_XATTR_CREATE;
	}
	return internal_flag;
}