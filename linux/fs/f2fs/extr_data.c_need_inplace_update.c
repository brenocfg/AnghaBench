#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct f2fs_io_info {TYPE_2__* page; } ;
struct TYPE_4__ {TYPE_1__* mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int f2fs_should_update_inplace (struct inode*,struct f2fs_io_info*) ; 
 scalar_t__ f2fs_should_update_outplace (struct inode*,struct f2fs_io_info*) ; 

__attribute__((used)) static inline bool need_inplace_update(struct f2fs_io_info *fio)
{
	struct inode *inode = fio->page->mapping->host;

	if (f2fs_should_update_outplace(inode, fio))
		return false;

	return f2fs_should_update_inplace(inode, fio);
}