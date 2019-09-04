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
struct page {int dummy; } ;
struct file {int dummy; } ;
struct address_space_operations {int (* write_end ) (struct file*,struct address_space*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page*,void*) ;} ;
struct address_space {struct address_space_operations* a_ops; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int stub1 (struct file*,struct address_space*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page*,void*) ; 

int pagecache_write_end(struct file *file, struct address_space *mapping,
				loff_t pos, unsigned len, unsigned copied,
				struct page *page, void *fsdata)
{
	const struct address_space_operations *aops = mapping->a_ops;

	return aops->write_end(file, mapping, pos, len, copied, page, fsdata);
}