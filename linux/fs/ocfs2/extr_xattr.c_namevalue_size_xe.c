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
typedef  scalar_t__ u64 ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_len; int /*<<< orphan*/  xe_value_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OCFS2_XATTR_INLINE_SIZE ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int namevalue_size (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ocfs2_xattr_is_local (struct ocfs2_xattr_entry*) ; 

__attribute__((used)) static int namevalue_size_xe(struct ocfs2_xattr_entry *xe)
{
	u64 value_len = le64_to_cpu(xe->xe_value_size);

	BUG_ON((value_len > OCFS2_XATTR_INLINE_SIZE) &&
	       ocfs2_xattr_is_local(xe));
	return namevalue_size(xe->xe_name_len, value_len);
}