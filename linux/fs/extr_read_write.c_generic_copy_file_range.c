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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t MAX_RW_COUNT ; 
 int /*<<< orphan*/  do_splice_direct (struct file*,int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

ssize_t generic_copy_file_range(struct file *file_in, loff_t pos_in,
				struct file *file_out, loff_t pos_out,
				size_t len, unsigned int flags)
{
	return do_splice_direct(file_in, &pos_in, file_out, &pos_out,
				len > MAX_RW_COUNT ? MAX_RW_COUNT : len, 0);
}