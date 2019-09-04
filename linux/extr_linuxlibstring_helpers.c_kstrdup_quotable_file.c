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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char*) ; 
 scalar_t__ PATH_MAX ; 
 char* file_path (struct file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 char* kstrdup_quotable (char*,int /*<<< orphan*/ ) ; 

char *kstrdup_quotable_file(struct file *file, gfp_t gfp)
{
	char *temp, *pathname;

	if (!file)
		return kstrdup("<unknown>", gfp);

	/* We add 11 spaces for ' (deleted)' to be appended */
	temp = kmalloc(PATH_MAX + 11, GFP_KERNEL);
	if (!temp)
		return kstrdup("<no_memory>", gfp);

	pathname = file_path(file, temp, PATH_MAX + 11);
	if (IS_ERR(pathname))
		pathname = kstrdup("<too_long>", gfp);
	else
		pathname = kstrdup_quotable(pathname, gfp);

	kfree(temp);
	return pathname;
}