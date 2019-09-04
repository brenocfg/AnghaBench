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
struct writeback_control {int dummy; } ;
struct inode {int dummy; } ;
struct address_space {struct inode* host; } ;
struct TYPE_2__ {scalar_t__ cp_task; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  FS_CP_DATA_IO ; 
 int /*<<< orphan*/  FS_DATA_IO ; 
 int __f2fs_write_data_pages (struct address_space*,struct writeback_control*,int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 

__attribute__((used)) static int f2fs_write_data_pages(struct address_space *mapping,
			    struct writeback_control *wbc)
{
	struct inode *inode = mapping->host;

	return __f2fs_write_data_pages(mapping, wbc,
			F2FS_I(inode)->cp_task == current ?
			FS_CP_DATA_IO : FS_DATA_IO);
}