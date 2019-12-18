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
struct core_name {int dummy; } ;
struct TYPE_2__ {char* comm; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int PTR_ERR (char*) ; 
 int cn_esc_printf (struct core_name*,char*,char*) ; 
 TYPE_1__* current ; 
 char* file_path (struct file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_mm_exe_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cn_print_exe_file(struct core_name *cn)
{
	struct file *exe_file;
	char *pathbuf, *path;
	int ret;

	exe_file = get_mm_exe_file(current->mm);
	if (!exe_file)
		return cn_esc_printf(cn, "%s (path unknown)", current->comm);

	pathbuf = kmalloc(PATH_MAX, GFP_KERNEL);
	if (!pathbuf) {
		ret = -ENOMEM;
		goto put_exe_file;
	}

	path = file_path(exe_file, pathbuf, PATH_MAX);
	if (IS_ERR(path)) {
		ret = PTR_ERR(path);
		goto free_buf;
	}

	ret = cn_esc_printf(cn, "%s", path);

free_buf:
	kfree(pathbuf);
put_exe_file:
	fput(exe_file);
	return ret;
}