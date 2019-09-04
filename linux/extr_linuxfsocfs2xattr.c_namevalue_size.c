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
typedef  int uint64_t ;

/* Variables and functions */
 int OCFS2_XATTR_INLINE_SIZE ; 
 int OCFS2_XATTR_ROOT_SIZE ; 
 int OCFS2_XATTR_SIZE (int) ; 

__attribute__((used)) static int namevalue_size(int name_len, uint64_t value_len)
{
	if (value_len > OCFS2_XATTR_INLINE_SIZE)
		return OCFS2_XATTR_SIZE(name_len) + OCFS2_XATTR_ROOT_SIZE;
	else
		return OCFS2_XATTR_SIZE(name_len) + OCFS2_XATTR_SIZE(value_len);
}