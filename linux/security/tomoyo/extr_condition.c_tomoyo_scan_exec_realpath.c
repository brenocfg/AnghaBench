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
struct tomoyo_path_info {int /*<<< orphan*/  name; } ;
struct tomoyo_name_union {int dummy; } ;
struct file {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int tomoyo_compare_name_union (struct tomoyo_path_info*,struct tomoyo_name_union const*) ; 
 int /*<<< orphan*/  tomoyo_fill_path_info (struct tomoyo_path_info*) ; 
 int /*<<< orphan*/  tomoyo_realpath_from_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tomoyo_scan_exec_realpath(struct file *file,
				      const struct tomoyo_name_union *ptr,
				      const bool match)
{
	bool result;
	struct tomoyo_path_info exe;

	if (!file)
		return false;
	exe.name = tomoyo_realpath_from_path(&file->f_path);
	if (!exe.name)
		return false;
	tomoyo_fill_path_info(&exe);
	result = tomoyo_compare_name_union(&exe, ptr);
	kfree(exe.name);
	return result == match;
}