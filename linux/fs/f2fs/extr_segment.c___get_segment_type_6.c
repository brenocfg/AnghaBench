#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_write_hint; } ;
struct f2fs_io_info {scalar_t__ type; TYPE_2__* page; } ;
struct TYPE_6__ {TYPE_1__* mapping; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int CURSEG_COLD_DATA ; 
 int CURSEG_COLD_NODE ; 
 int CURSEG_HOT_DATA ; 
 int CURSEG_HOT_NODE ; 
 int CURSEG_WARM_NODE ; 
 scalar_t__ DATA ; 
 int /*<<< orphan*/  FI_HOT_DATA ; 
 scalar_t__ IS_DNODE (TYPE_2__*) ; 
 scalar_t__ f2fs_is_atomic_file (struct inode*) ; 
 scalar_t__ f2fs_is_volatile_file (struct inode*) ; 
 int f2fs_rw_hint_to_seg_type (int /*<<< orphan*/ ) ; 
 scalar_t__ file_is_cold (struct inode*) ; 
 scalar_t__ file_is_hot (struct inode*) ; 
 scalar_t__ is_cold_data (TYPE_2__*) ; 
 scalar_t__ is_cold_node (TYPE_2__*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __get_segment_type_6(struct f2fs_io_info *fio)
{
	if (fio->type == DATA) {
		struct inode *inode = fio->page->mapping->host;

		if (is_cold_data(fio->page) || file_is_cold(inode))
			return CURSEG_COLD_DATA;
		if (file_is_hot(inode) ||
				is_inode_flag_set(inode, FI_HOT_DATA) ||
				f2fs_is_atomic_file(inode) ||
				f2fs_is_volatile_file(inode))
			return CURSEG_HOT_DATA;
		return f2fs_rw_hint_to_seg_type(inode->i_write_hint);
	} else {
		if (IS_DNODE(fio->page))
			return is_cold_node(fio->page) ? CURSEG_WARM_NODE :
						CURSEG_HOT_NODE;
		return CURSEG_COLD_NODE;
	}
}