#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_dir_lookup_result {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_parent; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int __ocfs2_add_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,struct buffer_head*,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocfs2_add_entry(handle_t *handle,
				  struct dentry *dentry,
				  struct inode *inode, u64 blkno,
				  struct buffer_head *parent_fe_bh,
				  struct ocfs2_dir_lookup_result *lookup)
{
	return __ocfs2_add_entry(handle, d_inode(dentry->d_parent),
				 dentry->d_name.name, dentry->d_name.len,
				 inode, blkno, parent_fe_bh, lookup);
}