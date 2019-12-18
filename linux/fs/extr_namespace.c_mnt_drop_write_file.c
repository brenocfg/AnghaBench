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
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mnt_drop_write_file (struct file*) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  sb_end_write (int /*<<< orphan*/ ) ; 

void mnt_drop_write_file(struct file *file)
{
	__mnt_drop_write_file(file);
	sb_end_write(file_inode(file)->i_sb);
}