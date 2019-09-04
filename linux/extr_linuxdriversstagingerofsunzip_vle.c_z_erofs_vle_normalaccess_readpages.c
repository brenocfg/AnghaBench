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
struct list_head {int dummy; } ;
struct file {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int __z_erofs_vle_normalaccess_readpages (struct file*,struct address_space*,struct list_head*,unsigned int,int) ; 

__attribute__((used)) static int z_erofs_vle_normalaccess_readpages(
	struct file *filp,
	struct address_space *mapping,
	struct list_head *pages, unsigned nr_pages)
{
	return __z_erofs_vle_normalaccess_readpages(filp,
		mapping, pages, nr_pages,
		nr_pages < 4 /* sync */);
}