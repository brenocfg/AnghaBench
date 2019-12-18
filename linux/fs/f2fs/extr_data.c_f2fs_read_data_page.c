#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EAGAIN ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 int f2fs_mpage_readpages (TYPE_1__*,int /*<<< orphan*/ *,struct page*,int,int) ; 
 int f2fs_read_inline_data (struct inode*,struct page*) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 
 int /*<<< orphan*/  trace_f2fs_readpage (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_read_data_page(struct file *file, struct page *page)
{
	struct inode *inode = page_file_mapping(page)->host;
	int ret = -EAGAIN;

	trace_f2fs_readpage(page, DATA);

	/* If the file has inline data, try to read it directly */
	if (f2fs_has_inline_data(inode))
		ret = f2fs_read_inline_data(inode, page);
	if (ret == -EAGAIN)
		ret = f2fs_mpage_readpages(page_file_mapping(page),
						NULL, page, 1, false);
	return ret;
}