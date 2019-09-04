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
struct path {int dummy; } ;
struct ovl_dir_file {int /*<<< orphan*/  is_upper; int /*<<< orphan*/  is_real; struct file* realfile; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {struct ovl_dir_file* private_data; TYPE_1__ f_path; int /*<<< orphan*/  f_flags; } ;
typedef  enum ovl_path_type { ____Placeholder_ovl_path_type } ovl_path_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  OVL_TYPE_UPPER (int) ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  kfree (struct ovl_dir_file*) ; 
 struct ovl_dir_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_dir_is_real (int /*<<< orphan*/ ) ; 
 struct file* ovl_path_open (struct path*,int /*<<< orphan*/ ) ; 
 int ovl_path_real (int /*<<< orphan*/ ,struct path*) ; 

__attribute__((used)) static int ovl_dir_open(struct inode *inode, struct file *file)
{
	struct path realpath;
	struct file *realfile;
	struct ovl_dir_file *od;
	enum ovl_path_type type;

	od = kzalloc(sizeof(struct ovl_dir_file), GFP_KERNEL);
	if (!od)
		return -ENOMEM;

	type = ovl_path_real(file->f_path.dentry, &realpath);
	realfile = ovl_path_open(&realpath, file->f_flags);
	if (IS_ERR(realfile)) {
		kfree(od);
		return PTR_ERR(realfile);
	}
	od->realfile = realfile;
	od->is_real = ovl_dir_is_real(file->f_path.dentry);
	od->is_upper = OVL_TYPE_UPPER(type);
	file->private_data = od;

	return 0;
}