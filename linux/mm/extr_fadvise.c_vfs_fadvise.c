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
struct file {TYPE_1__* f_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int (* fadvise ) (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int generic_fadvise (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int vfs_fadvise(struct file *file, loff_t offset, loff_t len, int advice)
{
	if (file->f_op->fadvise)
		return file->f_op->fadvise(file, offset, len, advice);

	return generic_fadvise(file, offset, len, advice);
}