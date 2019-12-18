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
struct page {int dummy; } ;
struct list_head {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int (* compress_pages ) (struct list_head*,struct address_space*,int /*<<< orphan*/ ,struct page**,unsigned long*,unsigned long*,unsigned long*) ;} ;

/* Variables and functions */
 int btrfs_compress_level (unsigned int) ; 
 TYPE_1__** btrfs_compress_op ; 
 int btrfs_compress_set_level (int,int) ; 
 int btrfs_compress_type (unsigned int) ; 
 struct list_head* get_workspace (int,int) ; 
 int /*<<< orphan*/  put_workspace (int,struct list_head*) ; 
 int stub1 (struct list_head*,struct address_space*,int /*<<< orphan*/ ,struct page**,unsigned long*,unsigned long*,unsigned long*) ; 

int btrfs_compress_pages(unsigned int type_level, struct address_space *mapping,
			 u64 start, struct page **pages,
			 unsigned long *out_pages,
			 unsigned long *total_in,
			 unsigned long *total_out)
{
	int type = btrfs_compress_type(type_level);
	int level = btrfs_compress_level(type_level);
	struct list_head *workspace;
	int ret;

	level = btrfs_compress_set_level(type, level);
	workspace = get_workspace(type, level);
	ret = btrfs_compress_op[type]->compress_pages(workspace, mapping,
						      start, pages,
						      out_pages,
						      total_in, total_out);
	put_workspace(type, workspace);
	return ret;
}