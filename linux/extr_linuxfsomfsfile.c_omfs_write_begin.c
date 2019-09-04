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
typedef  unsigned int loff_t ;

/* Variables and functions */
 int block_write_begin (struct address_space*,unsigned int,unsigned int,unsigned int,struct page**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omfs_get_block ; 
 int /*<<< orphan*/  omfs_write_failed (struct address_space*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int omfs_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata)
{
	int ret;

	ret = block_write_begin(mapping, pos, len, flags, pagep,
				omfs_get_block);
	if (unlikely(ret))
		omfs_write_failed(mapping, pos + len);

	return ret;
}