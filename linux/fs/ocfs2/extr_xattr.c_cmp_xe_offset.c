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
typedef  scalar_t__ u32 ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_offset; } ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_xe_offset(const void *a, const void *b)
{
	const struct ocfs2_xattr_entry *l = a, *r = b;
	u32 l_name_offset = le16_to_cpu(l->xe_name_offset);
	u32 r_name_offset = le16_to_cpu(r->xe_name_offset);

	if (l_name_offset < r_name_offset)
		return 1;
	if (l_name_offset > r_name_offset)
		return -1;
	return 0;
}