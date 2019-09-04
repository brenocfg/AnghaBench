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
struct file_operations {int dummy; } ;
struct file {int /*<<< orphan*/  f_mapping; int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct file*) ; 
 struct file* alloc_file (int /*<<< orphan*/ *,int,struct file_operations const*) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ *) ; 

struct file *alloc_file_clone(struct file *base, int flags,
				const struct file_operations *fops)
{
	struct file *f = alloc_file(&base->f_path, flags, fops);
	if (!IS_ERR(f)) {
		path_get(&f->f_path);
		f->f_mapping = base->f_mapping;
	}
	return f;
}