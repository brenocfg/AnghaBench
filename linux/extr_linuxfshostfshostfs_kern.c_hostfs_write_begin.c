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
struct address_space {int dummy; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 

__attribute__((used)) static int hostfs_write_begin(struct file *file, struct address_space *mapping,
			      loff_t pos, unsigned len, unsigned flags,
			      struct page **pagep, void **fsdata)
{
	pgoff_t index = pos >> PAGE_SHIFT;

	*pagep = grab_cache_page_write_begin(mapping, index, flags);
	if (!*pagep)
		return -ENOMEM;
	return 0;
}