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
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */

int finish_no_open(struct file *file, struct dentry *dentry)
{
	file->f_path.dentry = dentry;
	return 0;
}