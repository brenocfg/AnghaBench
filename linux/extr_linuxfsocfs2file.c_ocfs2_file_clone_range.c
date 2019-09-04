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
typedef  int /*<<< orphan*/  u64 ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ocfs2_reflink_remap_range (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocfs2_file_clone_range(struct file *file_in,
				  loff_t pos_in,
				  struct file *file_out,
				  loff_t pos_out,
				  u64 len)
{
	return ocfs2_reflink_remap_range(file_in, pos_in, file_out, pos_out,
					 len, false);
}