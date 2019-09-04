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

/* Variables and functions */
 unsigned long NO_COOKIE ; 
 unsigned long fast_get_dcookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_mm_exe_file (struct mm_struct*) ; 

__attribute__((used)) static unsigned long get_exec_dcookie(struct mm_struct *mm)
{
	unsigned long cookie = NO_COOKIE;
	struct file *exe_file;

	if (!mm)
		goto done;

	exe_file = get_mm_exe_file(mm);
	if (!exe_file)
		goto done;

	cookie = fast_get_dcookie(&exe_file->f_path);
	fput(exe_file);
done:
	return cookie;
}