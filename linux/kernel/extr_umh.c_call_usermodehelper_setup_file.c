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
struct umh_info {char* cmdline; } ;
struct subprocess_info {char* path; int (* init ) (struct subprocess_info*,struct cred*) ;void (* cleanup ) (struct subprocess_info*) ;void* data; struct file* file; int /*<<< orphan*/  work; int /*<<< orphan*/  argv; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_split (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_usermodehelper_exec_work ; 
 int /*<<< orphan*/  kfree (struct subprocess_info*) ; 
 struct subprocess_info* kzalloc (int,int /*<<< orphan*/ ) ; 

struct subprocess_info *call_usermodehelper_setup_file(struct file *file,
		int (*init)(struct subprocess_info *info, struct cred *new),
		void (*cleanup)(struct subprocess_info *info), void *data)
{
	struct subprocess_info *sub_info;
	struct umh_info *info = data;
	const char *cmdline = (info->cmdline) ? info->cmdline : "usermodehelper";

	sub_info = kzalloc(sizeof(struct subprocess_info), GFP_KERNEL);
	if (!sub_info)
		return NULL;

	sub_info->argv = argv_split(GFP_KERNEL, cmdline, NULL);
	if (!sub_info->argv) {
		kfree(sub_info);
		return NULL;
	}

	INIT_WORK(&sub_info->work, call_usermodehelper_exec_work);
	sub_info->path = "none";
	sub_info->file = file;
	sub_info->init = init;
	sub_info->cleanup = cleanup;
	sub_info->data = data;
	return sub_info;
}