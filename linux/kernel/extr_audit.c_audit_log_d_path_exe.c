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
struct mm_struct {int dummy; } ;
struct file {int /*<<< orphan*/  f_path; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_d_path (struct audit_buffer*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_mm_exe_file (struct mm_struct*) ; 

void audit_log_d_path_exe(struct audit_buffer *ab,
			  struct mm_struct *mm)
{
	struct file *exe_file;

	if (!mm)
		goto out_null;

	exe_file = get_mm_exe_file(mm);
	if (!exe_file)
		goto out_null;

	audit_log_d_path(ab, " exe=", &exe_file->f_path);
	fput(exe_file);
	return;
out_null:
	audit_log_format(ab, " exe=(null)");
}