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
struct object_info {int dummy; } ;
struct adfs_dir {int pos; } ;

/* Variables and functions */
 unsigned int __adfs_dir_get (struct adfs_dir*,int,struct object_info*) ; 

__attribute__((used)) static int
adfs_f_getnext(struct adfs_dir *dir, struct object_info *obj)
{
	unsigned int ret;

	ret = __adfs_dir_get(dir, dir->pos, obj);
	if (ret == 0)
		dir->pos += 26;

	return ret;
}