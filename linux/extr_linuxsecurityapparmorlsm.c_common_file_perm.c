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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct aa_label {int dummy; } ;
struct TYPE_4__ {scalar_t__ dentry; } ;

/* Variables and functions */
 int EACCES ; 
 struct aa_label* __begin_current_label_crit_section () ; 
 int /*<<< orphan*/  __end_current_label_crit_section (struct aa_label*) ; 
 int aa_file_perm (char const*,struct aa_label*,struct file*,int /*<<< orphan*/ ) ; 
 TYPE_2__ aa_null ; 

__attribute__((used)) static int common_file_perm(const char *op, struct file *file, u32 mask)
{
	struct aa_label *label;
	int error = 0;

	/* don't reaudit files closed during inheritance */
	if (file->f_path.dentry == aa_null.dentry)
		return -EACCES;

	label = __begin_current_label_crit_section();
	error = aa_file_perm(op, label, file, mask);
	__end_current_label_crit_section(label);

	return error;
}