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
struct mm_struct {int dummy; } ;
struct file {int /*<<< orphan*/  f_path; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_mm_exe_file (struct mm_struct*) ; 
 char* tomoyo_realpath_from_path (int /*<<< orphan*/ *) ; 

const char *tomoyo_get_exe(void)
{
	struct file *exe_file;
	const char *cp;
	struct mm_struct *mm = current->mm;

	if (!mm)
		return NULL;
	exe_file = get_mm_exe_file(mm);
	if (!exe_file)
		return NULL;

	cp = tomoyo_realpath_from_path(&exe_file->f_path);
	fput(exe_file);
	return cp;
}