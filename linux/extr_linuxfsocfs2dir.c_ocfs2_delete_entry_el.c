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
struct ocfs2_dir_entry {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int __ocfs2_delete_entry (int /*<<< orphan*/ *,struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_delete_entry_el(handle_t *handle,
					struct inode *dir,
					struct ocfs2_dir_entry *de_del,
					struct buffer_head *bh)
{
	return __ocfs2_delete_entry(handle, dir, de_del, bh, bh->b_data,
				    bh->b_size);
}