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
struct file {struct address_space* f_mapping; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  __filemap_fdatawait_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int file_check_and_advance_wb_err (struct file*) ; 

int file_fdatawait_range(struct file *file, loff_t start_byte, loff_t end_byte)
{
	struct address_space *mapping = file->f_mapping;

	__filemap_fdatawait_range(mapping, start_byte, end_byte);
	return file_check_and_advance_wb_err(file);
}