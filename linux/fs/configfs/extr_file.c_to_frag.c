#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct configfs_fragment {int dummy; } ;
struct configfs_dirent {struct configfs_fragment* s_frag; } ;
struct TYPE_3__ {struct configfs_dirent* d_fsdata; } ;

/* Variables and functions */

__attribute__((used)) static inline struct configfs_fragment *to_frag(struct file *file)
{
	struct configfs_dirent *sd = file->f_path.dentry->d_fsdata;

	return sd->s_frag;
}