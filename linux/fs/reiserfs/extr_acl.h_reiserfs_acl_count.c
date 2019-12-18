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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  reiserfs_acl_header ;
typedef  int /*<<< orphan*/  reiserfs_acl_entry_short ;
typedef  int /*<<< orphan*/  reiserfs_acl_entry ;

/* Variables and functions */

__attribute__((used)) static inline int reiserfs_acl_count(size_t size)
{
	ssize_t s;
	size -= sizeof(reiserfs_acl_header);
	s = size - 4 * sizeof(reiserfs_acl_entry_short);
	if (s < 0) {
		if (size % sizeof(reiserfs_acl_entry_short))
			return -1;
		return size / sizeof(reiserfs_acl_entry_short);
	} else {
		if (s % sizeof(reiserfs_acl_entry))
			return -1;
		return s / sizeof(reiserfs_acl_entry) + 4;
	}
}